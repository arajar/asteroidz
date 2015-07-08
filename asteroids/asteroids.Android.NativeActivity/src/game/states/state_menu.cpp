#include "state_menu.h"
#include "state_gameplay.h"
#include "../game.h"

void stateMenu::start()
{
	m_background.init("menu_background.bmp");

	m_projection = math::ortho(0.0f, m_screenSize.x, m_screenSize.y, 0.0f, -1.f, 1000.f);
	m_projection *= math::translate(math::mat4(), math::vec3(0, 0, -100));

	glm::mat4 proj = glm::ortho(0.f, m_screenSize.x, m_screenSize.y, 0.f, -1.f, 1000.f);
	proj *= glm::translate(glm::mat4(), glm::vec3(0, 0, -100));

	int a = 3;
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
	math::mat4 o1 = math::ortho(0.0f, m_screenSize.x, m_screenSize.y, 0.0f, -1.f, 1000.f);
	glm::mat4 o2 = glm::ortho(0.0f, m_screenSize.x, m_screenSize.y, 0.0f, -1.f, 1000.f);

	math::mat4 t1 = math::translate(math::mat4(), math::vec3(100, 0, 50));
	glm::mat4 t2 = glm::translate(glm::mat4(), glm::vec3(100, 0, 50));

	math::mat4 r1 = math::rotate(math::mat4(), 20.f, math::vec3(0, 0, 1));
	glm::mat4 r2 = glm::rotate(glm::mat4(), 20.f, glm::vec3(0, 0, 1));

	math::mat4 s1 = math::scale(math::mat4(), math::vec3(10, 20, 30));
	glm::mat4 s2 = glm::scale(glm::mat4(), glm::vec3(10, 20, 30));

	auto a1 = t1 * r1;
	auto b1 = t2 * r2;

	int a = 3;

}

void stateMenu::render()
{
	m_background.render(m_projection);
}

