#include "game.h"
#include "states/state_menu.h"

// Fixed to 30 fps
const int Game::FPS = 30;
const float Game::TIME_PER_FRAME = Game::FPS / 100.f;

Game::Game(const char* name)
	: m_stateMgr(nullptr)
	, m_appName(name)
	, m_initialized(false)
	, m_running(false)
	, m_shouldClose(false)
{
}

Game::~Game()
{
}

bool Game::init(struct android_app* state)
{
	if (!m_initialized)
	{
		m_applicationState = state;
		m_stateMgr = new states::manager;

		m_initialized = true;
	}

	return m_applicationState != nullptr;
}

int Game::initDisplay()
{
	const EGLint RGBX_8888_ATTRIBS[] =
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE,
		EGL_WINDOW_BIT, EGL_BLUE_SIZE, 8, EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8, EGL_DEPTH_SIZE, 8, EGL_NONE
	};

	const EGLint RGB_565_ATTRIBS[] =
	{
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT, EGL_SURFACE_TYPE,
		EGL_WINDOW_BIT, EGL_BLUE_SIZE, 5, EGL_GREEN_SIZE, 6,
		EGL_RED_SIZE, 5, EGL_DEPTH_SIZE, 8, EGL_NONE
	};

	const EGLint* attribList;

	int windowFormat = ANativeWindow_getFormat(m_applicationState->window);
	if ((windowFormat == WINDOW_FORMAT_RGBA_8888) || (windowFormat == WINDOW_FORMAT_RGBX_8888))
	{
		attribList = RGBX_8888_ATTRIBS;
	}
	else
	{
		attribList = RGB_565_ATTRIBS;
	}

	EGLint format;
	EGLint numConfigs;
	EGLConfig config;

	m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(m_display, 0, 0);

	eglChooseConfig(m_display, attribList, &config, 1, &numConfigs);
	eglGetConfigAttrib(m_display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(m_applicationState->window, 0, 0, format);

	m_surface = eglCreateWindowSurface(m_display, config, m_applicationState->window, nullptr);

	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	m_context = eglCreateContext(m_display, config, EGL_NO_CONTEXT, contextAttribs);

	if (eglMakeCurrent(m_display, m_surface, m_surface, m_context) == EGL_FALSE)
	{
		LOGW("Unable to emathakeCurrent");
		return -1;
	}

	eglQuerySurface(m_display, m_surface, EGL_WIDTH, &m_width);
	eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &m_height);

	glViewport(0, 0, m_width, m_height);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_stateMgr->setState<stateMenu>(math::vec2(m_width, m_height));
	return 0;
}

void Game::run()
{
	m_running = true;

	while (m_applicationState->destroyRequested == 0)
	{
		int ident;
		int events;
		struct android_poll_source* source;

		// Check for events
		while ((ident = ALooper_pollAll(m_running ? 0 : -1, nullptr, &events, (void**)&source)) >= 0)
		{
			if (source != nullptr)
			{
				source->process(m_applicationState, source);
			}
		}

		if (m_running && displayInitialized())
		{
			// Fixed update time to 30 fps for the sake of simplicity
			update(TIME_PER_FRAME);
			render();
		}
	}

	// Check if we are exiting.
	if (m_applicationState->destroyRequested != 0)
	{
		shutdown();
	}
}

bool Game::displayInitialized() const
{
	return m_applicationState->window != nullptr;
}

void Game::pause()
{
	m_running = false;
}

void Game::resume()
{
	m_running = true;
}

void Game::update(float dt)
{
	// game logic goes here
	m_stateMgr->update(dt);
}

void Game::handleCommands(struct android_app* app, int32_t cmd)
{
	auto game = (Game*)app->userData;
	game->internalHandleCommands(cmd);
}

int32_t Game::handleInput(struct android_app* app, AInputEvent* event)
{
	auto game = (Game*)app->userData;

	return game->internalHandleInput(event);
}

void Game::internalHandleCommands(int32_t cmd)
{
	switch (cmd)
	{
	case APP_CMD_INIT_WINDOW:
		// The window is being shown, get it ready.
		if (displayInitialized())
		{
			initDisplay();
		}
		break;
	case APP_CMD_TERM_WINDOW:
		// The window is being hidden or closed, clean it up.
		//shutdown();
		break;
	case APP_CMD_GAINED_FOCUS:
		resume();
		break;
	case APP_CMD_LOST_FOCUS:
		pause();
		break;
	}
}

int32_t Game::internalHandleInput(AInputEvent* event)
{
	// Touch event
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{
		// Check for multi touch, and also restrict touches to 2
		size_t pointerCount = AMotionEvent_getPointerCount(event);
		for (size_t touchId = 0; touchId < pointerCount && touchId < 2; ++touchId)
		{
			int32_t action = AMotionEvent_getAction(event);
			unsigned int flags = action & AMOTION_EVENT_ACTION_MASK;
			switch (flags)
			{
			case AMOTION_EVENT_ACTION_POINTER_DOWN:
			case AMOTION_EVENT_ACTION_MOVE:
			case AMOTION_EVENT_ACTION_DOWN:
				ev[touchId].action = input::Action::Down;
				ev[touchId].x = AMotionEvent_getX(event, touchId);
				ev[touchId].y = AMotionEvent_getY(event, touchId);
				ev[touchId].alpha = 1.f;
				break;
			case AMOTION_EVENT_ACTION_POINTER_UP:
			case AMOTION_EVENT_ACTION_UP:
				ev[touchId].action = input::Action::Up;
				break;
			}

			m_stateMgr->handleEvents(ev[touchId]);
		}
		return 1;
	}

	if (AKeyEvent_getKeyCode(event) == AKEYCODE_BACK)
	{
		m_stateMgr->setState<stateMenu>(math::vec2(m_width, m_height));

		//backButtonPushed();
		// Exit the game
		//ANativeActivity_finish(m_applicationState->activity);
		return 1;
	};

	return 0;
}

void Game::backButtonPushed()
{
	shutdown();
}

void Game::beginFrame()
{
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Game::renderFrame()
{
	m_stateMgr->render();
}

void Game::endFrame()
{
	eglSwapBuffers(m_display, m_surface);
}

void Game::render()
{
	beginFrame();
	renderFrame();
	endFrame();
}

void Game::shutdown()
{
	if (m_display != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(m_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

		if (m_context != EGL_NO_CONTEXT)
		{
			eglDestroyContext(m_display, m_context);
		}

		if (m_surface != EGL_NO_SURFACE)
		{
			eglDestroySurface(m_display, m_surface);
		}

		eglTerminate(m_display);
	}

	m_running = false;
	m_display = EGL_NO_DISPLAY;
	m_context = EGL_NO_CONTEXT;
	m_surface = EGL_NO_SURFACE;
}
