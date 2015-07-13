#include "state_gameplay.h"
#include "state_menu.h"
#include <random>

#include "../entities/renderSystem.h"
#include "../entities/movementSystem.h"
#include "../entities/spawnSystem.h"
#include "../entities/collisionSystem.h"
#include "../entities/shootSystem.h"
#include "../entities/debugRenderSystem.h"

#include "../game.h"

void stateGameplay::start()
{
	background.init("game_background.bmp");
	m_leftJoy.init();
	m_leftJoy.m_position = { 200.f, m_screenSize.y - 200 };

	m_rightJoy.init();
	m_rightJoy.m_position = { m_screenSize.x - 200, m_screenSize.y - 200 };

	m_projection = math::ortho(0.0f, m_screenSize.x, m_screenSize.y, 0.0f, -1.f, 1000.f);
	m_projection *= math::translate(math::mat4(), math::vec3(0, 0, -100));
	
	m_leftJoy.m_projection = m_projection;
	m_rightJoy.m_projection = m_projection;

	ps::manager::init(m_projection);

	auto renderSystem = m_world.add<e::renderSystem>();
	renderSystem->setWindowSize(m_screenSize);

	m_world.add<e::collisionSystem>();
#if defined DEBUG_COLLISIONS
	m_world.add<e::debugRenderSystem>();
#endif
	auto movement = m_world.add<e::movementSystem>();
	movement->setWindowSize(m_screenSize);

	auto shoot = m_world.add<e::shootSystem>();
	shoot->setJoy(&m_rightJoy);
	
	m_world.add<e::spawnSystem>();

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
	m_shipType = typ;
	col->colRadius = 31.f;
	util::createShip(ren, 2.f);
#if defined DEBUG_COLLISIONS
	auto deb = m_world.add<e::debugRenderable>(m_ship);
	util::createDebugCircle(deb, col->colRadius);
#endif

	auto mis = m_world.add<e::missileArray>(m_ship);
	mis->radius = 10.f;
	util::createMissile(&mis->ren, 10.f);

	auto linearInterpolation = [](float val)
	{
		return val;
	};

	m_timer.setEaseFunction(linearInterpolation);
	m_timer.reset(0.f, 1.f);
	m_timer.setDelay(50.f);
}

void stateGameplay::resume()
{
}

void stateGameplay::suspend()
{
}

void stateGameplay::end()
{
}

void stateGameplay::handleEvents(const input::TouchEvent& ev)
{
	if (ev.x < m_screenSize.x / 2)
	{
		m_leftJoy.handleInput(ev);
	}
	else if (ev.x > m_screenSize.x / 2)
	{
		m_rightJoy.handleInput(ev);
	}

	auto dir = m_world.get<e::direction>(m_ship);
	if (dir)
	{
		dir->angle = -m_leftJoy.m_angle;
	}

	auto acc = m_world.get<e::acceleration>(m_ship);
	if (acc)
	{
		acc->acc = m_leftJoy.m_acceleration * 5.f;
	}
}

void stateGameplay::update(float deltaTime)
{
	m_leftJoy.update(deltaTime);
	m_rightJoy.update(deltaTime);
	ps::manager::update();
	
	// if the player's ship is still alive, update the entity component system
	if (m_shipType->alive)
	{
		m_world(deltaTime);
	}
	else
	{
		// if the player just died, wait a moment while the particles are still moving
		m_timer.update(deltaTime);
		if (m_timer.hasFinished())
		{
			// then, go to the main menu
			Game::getInstance()->getStateManager()->setState<stateMenu>(m_screenSize);
		}
	}
}

void stateGameplay::render()
{
	background.render(m_projection, m_screenSize);

	// if the ship is alive, render all the entities
	if (m_shipType->alive)
	{
		m_world();
	}

	ps::manager::render();

	m_leftJoy.render();
	m_rightJoy.render();

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		LOGI("ast error %d", error);
	}
}

