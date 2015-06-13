#pragma once

#include <string>

class Game
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

public: // callbacks

public:
	void update(float dt);

protected:
	void beginFrame();
	void renderFrame();
	void endFrame();

private:
	void render();

protected:
	const char* m_appName;

protected:
	bool m_running;
	bool m_shouldClose;

protected:
	EGLDisplay m_display;
	EGLSurface m_surface;
	EGLContext m_context;
	int32_t m_width;
	int32_t m_height;

	struct android_app* m_state;
};