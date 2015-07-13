#include "game/game.h"

//////////////////////////////////////////////////////////////////////////

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "asteroids.NativeActivity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "asteroids.NativeActivity", __VA_ARGS__))

//////////////////////////////////////////////////////////////////////////

// Our entry point to the application
void android_main(struct android_app* state)
{
	// create the game singleton
	new Game("asteroids");

	state->userData = Game::getInstance();
	state->onAppCmd = &Game::handleCommands;
	state->onInputEvent = &Game::handleInput;

	// Pass the asset manager to the filesystem helper
	util::setAssetMgr(state->activity->assetManager);

	if (Game::getInstance()->init(state))
	{
		Game::getInstance()->run();
	}

	Game::destroy();
}

//////////////////////////////////////////////////////////////////////////
