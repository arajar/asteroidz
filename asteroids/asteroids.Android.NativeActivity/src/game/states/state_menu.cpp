#include "state_menu.h"
#include <random>

#include "../entities/renderSystem.h"
#include "../entities/movementSystem.h"
#include "../entities/spawnSystem.h"
#include "../entities/collisionSystem.h"
#include "../entities/shootSystem.h"
#include "../entities/debugRenderSystem.h"

//gfx::fbo* fbo;

input::virtualJoystick* leftJoy;
input::virtualJoystick* rightJoy;

void stateMenu::start()
{
	leftJoy = new input::virtualJoystick;
	leftJoy->init();
	leftJoy->m_position = { 200.f, m_screenSize.y - 200 };

	rightJoy = new input::virtualJoystick;
	rightJoy->init();
	rightJoy->m_position = { m_screenSize.x - 200, m_screenSize.y - 200 };

	//fbo = new gfx::fbo(m_screenSize);
	//auto sh = new gfx::shader;
	//sh->vertex("circle.vs.glsl").pixel("circle.ps.glsl").link();
	//fbo->init(sh);

	glm::mat4 projection = glm::ortho(0.0f, m_screenSize.x, m_screenSize.y, 0.0f, -1.f, 1000.f);
	projection *= glm::translate(glm::mat4(), glm::vec3(0, 0, -100));
	leftJoy->m_projection = projection;
	rightJoy->m_projection = projection;

	auto renderSystem = m_world.add<e::renderSystem>();
	renderSystem->setWindowSize(m_screenSize);

	m_world.add<e::spawnSystem>();
	m_world.add<e::collisionSystem>();
#if defined DEBUG_COLLISIONS
	m_world.add<e::debugRenderSystem>();
#endif
	auto movement = m_world.add<e::movementSystem>();
	movement->setWindowSize(m_screenSize);

	auto shoot = m_world.add<e::shootSystem>();
	shoot->setJoy(rightJoy);

	m_ship = m_world.createEntity();

	auto pos = m_world.add<e::position>(m_ship);
	auto dir = m_world.add<e::direction>(m_ship);
	auto ren = m_world.add<e::renderable>(m_ship);
	auto acc = m_world.add<e::acceleration>(m_ship);
	auto rot = m_world.add<e::localRotation>(m_ship);
	auto typ = m_world.add<e::entityType>(m_ship);
	auto col = m_world.add<e::collision>(m_ship);

	pos->pos = m_screenSize / 2.f;
	dir->angle = 0;
	acc->acc = 0.f;
	rot->rotation = 0;
	typ->type = e::EntityType::Player;
	col->colRadius = 31.f;
	util::createShip(ren, 2.f);
#if defined DEBUG_COLLISIONS
	auto deb = m_world.add<e::debugRenderable>(m_ship);
	util::createDebugCircle(deb, col->colRadius);
#endif

	auto mis = m_world.add<e::missileArray>(m_ship);
	mis->radius = 10.f;
	util::createMissile(&mis->ren, 10.f);
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
	if (ev.x < m_screenSize.x / 2)
	{
		leftJoy->handleInput(ev);
	}
	else if (ev.x > m_screenSize.x / 2)
	{
		rightJoy->handleInput(ev);
	}

	auto dir = m_world.get<e::direction>(m_ship);
	if (dir)
	{
		dir->angle = -leftJoy->m_angle;
	}

	auto acc = m_world.get<e::acceleration>(m_ship);
	if (acc)
	{
		acc->acc = leftJoy->m_acceleration * 5.f;
	}
}

void stateMenu::update(float deltaTime)
{
	leftJoy->update(deltaTime);
	rightJoy->update(deltaTime);
	m_world(deltaTime);
}

void stateMenu::render()
{
	// render everything to the fbo
	//fbo->begin();
	m_world();
	//fbo->end();

	// render the contents of the fbo with the postfx
	//fbo->render();

	leftJoy->render();
	rightJoy->render();

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		LOGI("ast error %d", error);
	}
}

