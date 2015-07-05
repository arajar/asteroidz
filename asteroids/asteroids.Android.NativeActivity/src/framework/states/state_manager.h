#pragma once

//////////////////////////////////////////////////////////////////////////

#include "state.h"
#include <vector>

//////////////////////////////////////////////////////////////////////////

namespace states
{
	class manager
	{
	public:
		manager();
		virtual ~manager() {}

	public:
		void update(float deltaTime);
		void render();
		void handleEvents(const input::TouchEvent& ev);

	public:
		state* getCurrentState();

		template<typename S>
		S* getState();

		template<typename S, class... _Types>
		void setState(_Types&&... _Args);

		template<typename S, class... _Types>
		void pushState(_Types&&... _Args);

		bool popState();
		void popAllStates();

		template<typename S>
		bool isStateInStack() const;

		template<typename S>
		bool is() const;

	public:
		std::vector<state*> m_states;
	};

	//////////////////////////////////////////////////////////////////////////

	template <typename S>
	S* manager::getState()
	{
		for (auto& state : m_states)
		{
			auto s = static_cast<S*>(state);
			if (s != nullptr)
			{
				return s;
			}
		}

		return nullptr;
	}

	//////////////////////////////////////////////////////////////////////////

	template <typename S, class ... _Types>
	void manager::setState(_Types&&... _Args)
	{
		popAllStates();
		pushState<S>(std::forward<_Types>(_Args)...);
	}

	//////////////////////////////////////////////////////////////////////////

	template <typename S, class ... _Types>
	void manager::pushState(_Types&&... _Args)
	{
		if (!m_states.empty())
		{
			auto currentState = getCurrentState();
			if (currentState != nullptr)
			{
				currentState->suspend();
			}

			if (isStateInStack<S>())
			{
				auto state = getState<S>();
				m_states.push_back(state);
				state->resume();
				return;
			}
		}

		auto state = new S(_Args...);
		m_states.push_back(state);
		state->start();
		state->resume();
	}

	//////////////////////////////////////////////////////////////////////////
	
	template <typename S>
	bool manager::isStateInStack() const
	{
		for (auto& state : m_states)
		{
			if (static_cast<S*>(state))
			{
				return true;
			}
		}

		return false;
	}

	//////////////////////////////////////////////////////////////////////////
	
	template <typename S>
	bool manager::is() const
	{
		return dynamic_cast<S*>(m_states.back()) != nullptr;
	}
}