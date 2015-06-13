#include "framework/game.h"
#include "framework/vec2.h"
#include "framework/file_utils.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "asteroids.NativeActivity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "asteroids.NativeActivity", __VA_ARGS__))

/**
* Our saved state data.
*/
struct saved_state
{
	float angle;
	int32_t x;
	int32_t y;
};

/**
* Process the next input event.
*/
static int32_t engine_handle_input(struct android_app* app, AInputEvent* event)
{
	//struct engine* engine = (struct engine*)app->userData;

	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{
		//engine->state.x = AMotionEvent_getX(event, 0);
		//engine->state.y = AMotionEvent_getY(event, 0);
		return 1;
	}

	return 0;
}

/**
* Process the next main command.
*/
static void engine_handle_cmd(struct android_app* app, int32_t cmd)
{
	Game* game = (Game*)app->userData;
	switch (cmd)
	{
	case APP_CMD_INIT_WINDOW:
		// The window is being shown, get it ready.
		if (game->displayInitialized())
		{
			game->initDisplay();
		}
		break;
	case APP_CMD_TERM_WINDOW:
		// The window is being hidden or closed, clean it up.
		game->shutdown();
		break;
	case APP_CMD_GAINED_FOCUS:
		game->resume();
		break;
	case APP_CMD_LOST_FOCUS:
		game->pause();
		break;
	}
}

void android_main(struct android_app* state)
{
	Game game("asteroids");

	state->userData = &game;
	state->onAppCmd = engine_handle_cmd;
	state->onInputEvent = engine_handle_input;

	// Pass the asset manager to the filesystem helper
	util::fs::mgr = state->activity->assetManager;

	if (game.init(state))
	{
		game.run();
	}
}
