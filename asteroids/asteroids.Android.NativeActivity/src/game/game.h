#pragma once

#include <string>
#include "../framework/states/state_manager.h"
#include "../framework/util/singleton.h"

class Game : public Singleton<Game>
{
public:
	static const int FPS;
	static const float TIME_PER_FRAME;

public:
	Game(const char* name);
	virtual ~Game();

public:
	bool init(struct android_app* state);
	int initDisplay();
	void shutdown();

	void run();

	bool displayInitialized() const;

	void pause();
	void resume();

public:
	void update(float dt);

	states::manager* getStateManager() const { return m_stateMgr; }

public: // callbacks
	static void handleCommands(struct android_app* app, int32_t cmd);
	static int32_t handleInput(struct android_app* app, AInputEvent* event);

protected:
	void internalHandleCommands(int32_t cmd);
	int32_t internalHandleInput(AInputEvent* event);

protected:
	void backButtonPushed();

protected:
	void beginFrame();
	void renderFrame();
	void endFrame();

private:
	void render();

protected:
	states::manager* m_stateMgr;

protected:
	const char* m_appName;

protected:
	bool m_initialized;
	bool m_running;
	bool m_shouldClose;

	input::TouchEvent ev[2];

private:
	EGLDisplay m_display;
	EGLSurface m_surface;
	EGLContext m_context;
	int32_t m_width;
	int32_t m_height;

	struct android_app* m_applicationState;
};