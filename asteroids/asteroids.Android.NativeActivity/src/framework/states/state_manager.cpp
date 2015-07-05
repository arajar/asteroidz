#include "state_manager.h"

//////////////////////////////////////////////////////////////////////////

namespace states
{
	manager::manager()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void manager::update(float deltaTime)
	{
		if (!m_states.empty())
		{
			m_states.back()->update(deltaTime);
		}
	}
	
	//////////////////////////////////////////////////////////////////////////

	void manager::render()
	{
		if (!m_states.empty())
		{
			m_states.back()->render();
		}
	}

	//////////////////////////////////////////////////////////////////////////
	
	void manager::handleEvents(const input::TouchEvent& ev)
	{
		if (!m_states.empty())
		{
			m_states.back()->handleEvents(ev);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	
	state* manager::getCurrentState()
	{
		return m_states.back();
	}

	//////////////////////////////////////////////////////////////////////////

	bool manager::popState()
	{
		if (!m_states.empty())
		{
			auto lastState = m_states.back();
			lastState->suspend();
			lastState->end();
			m_states.pop_back();
		}

		return m_states.empty();
	}

	//////////////////////////////////////////////////////////////////////////

	void manager::popAllStates()
	{
		if (!m_states.empty())
		{
			auto lastState = m_states.back();
			lastState->suspend();
		}

		while (!m_states.empty())
		{
			auto lastState = m_states.back();
			lastState->end();
			m_states.pop_back();
		}
	}
}