#include "state_menu.h"
#include "state_gameplay.h"
#include "../game.h"

void stateMenu::start()
{
	m_background.init("menu_background.bmp");

	m_projection = math::ortho(0.0f, m_screenSize.x, m_screenSize.y, 0.0f, -1.f, 1000.f);
	m_projection *= math::translate(math::mat4(), math::vec3(0, 0, 1));
}

void stateMenu::resume()
{
}

void stateMenu::suspend()
{
}

void stateMenu::end()
{
}

void stateMenu::handleEvents(const input::TouchEvent& ev)
{
	if (ev.action == input::Action::Up)
	{
		Game::getInstance()->getStateManager()->setState<stateGameplay>(m_screenSize);
	}
}

void stateMenu::update(float deltaTime)
{
}

void stateMenu::render()
{
	m_background.render(m_projection, m_screenSize);
}

