#include "game/game.h"

//////////////////////////////////////////////////////////////////////////

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "asteroids.NativeActivity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "asteroids.NativeActivity", __VA_ARGS__))

//////////////////////////////////////////////////////////////////////////

void android_main(struct android_app* state)
{
	Game game("asteroids");

	state->userData = &game;
	state->onAppCmd = &Game::handleCommands;
	state->onInputEvent = &Game::handleInput;

	// Pass the asset manager to the filesystem helper
	util::setAssetMgr(state->activity->assetManager);

	if (game.init(state))
	{
		game.run();
	}
}

//////////////////////////////////////////////////////////////////////////
