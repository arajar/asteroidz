#include "game.h"

// Fixed to 30 fps
const int Game::FPS = 30;
const float Game::TIME_PER_FRAME = 1000.f / Game::FPS;

Game::Game(const char* name)
	: m_appName(name)
	, m_running(false)
	, m_shouldClose(false)
{
}

Game::~Game()
{
}

bool Game::init(struct android_app* state)
{
	m_state = state;
}

int Game::initDisplay()
{
	const EGLint attribs[] =
	{
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_NONE
	};

	EGLint format;
	EGLint numConfigs;
	EGLConfig config;

	m_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(m_display, 0, 0);

	eglChooseConfig(m_display, attribs, &config, 1, &numConfigs);
	eglGetConfigAttrib(m_display, config, EGL_NATIVE_VISUAL_ID, &format);

	ANativeWindow_setBuffersGeometry(m_state->window, 0, 0, format);

	m_surface = eglCreateWindowSurface(m_display, config, m_state->window, nullptr);
	m_context = eglCreateContext(m_display, config, nullptr, nullptr);

	if (eglMakeCurrent(m_display, m_surface, m_surface, m_context) == EGL_FALSE)
	{
	//	LOGW("Unable to eglMakeCurrent");
		return -1;
	}

	eglQuerySurface(m_display, m_surface, EGL_WIDTH, &m_width);
	eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &m_height);

	return 0;
}

void Game::run()
{
	m_running = true;

	while (m_state->destroyRequested == 0)
	{
		int ident;
		int events;
		struct android_poll_source* source;

		// Check for events
		while ((ident = ALooper_pollAll(m_running ? 0 : -1, nullptr, &events, (void**)&source)) >= 0)
		{
			if (source != nullptr)
			{
				source->process(m_state, source);
			}
		}

		if (m_running && displayInitialized())
		{
			update(TIME_PER_FRAME);
			render();
		}
	}

	// Check if we are exiting.
	if (m_state->destroyRequested != 0)
	{
		shutdown();
	}
}

bool Game::displayInitialized() const
{
	return m_state->window != nullptr;
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
}

void Game::beginFrame()
{
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::renderFrame()
{
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
