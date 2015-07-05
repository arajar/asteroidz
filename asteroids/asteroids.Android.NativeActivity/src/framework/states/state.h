#pragma once
#include <memory>

//////////////////////////////////////////////////////////////////////////

namespace states
{
	class state
	{
	public:
		state() {}

		virtual ~state() {}

		virtual void start() = 0;
		virtual void resume() = 0;
		virtual void suspend() = 0;
		virtual void end() = 0;

	public:
		virtual void handleEvents(const input::TouchEvent& ev) { }
		virtual void update(float deltaTime) { }
		virtual void render() { }
	};
}