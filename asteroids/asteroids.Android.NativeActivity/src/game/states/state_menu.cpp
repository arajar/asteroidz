#include "state_menu.h"
#include <random>

#include "../entities/renderSystem.h"
#include "../entities/movementSystem.h"

gfx::camera cam;
gfx::fbo* fbo;

input::virtualJoystick* joy;

void stateMenu::start()
{
	//joy = new input::virtualJoystick;
	//joy->init();
	//joy->m_position = { 0, 0 };

	cam.setPosition(m::vec3(0, 0, 30));
	cam.setViewportAspectRatio(1804.f / (float)1080.f);

	fbo = new gfx::fbo(m::vec2(1804.f, 1080.f));
	auto sh = new gfx::shader;
	sh->vertex("default.vs.glsl").pixel("default.ps.glsl").link();
	fbo->init(sh);

	auto render = m_world.add<e::renderSystem>();
	render->addCamera(&cam);

	auto movement = m_world.add<e::movementSystem>();
	movement->setWindowSize(m_screenSize);

	auto ship = m_world.createEntity();

	auto pos = m_world.add<e::position>(ship);
	auto dir = m_world.add<e::direction>(ship);
	auto ren = m_world.add<e::renderable>(ship);
	auto acc = m_world.add<e::acceleration>(ship);

	pos->pos = m::vec2(0, 0);
	dir->angle = 0;
	acc->acc = 1.f;
	util::createShip(ren);

	for (size_t i = 0; i < 10; i++)
	{
		auto asteroid = m_world.createEntity();

		auto pos = m_world.add<e::position>(asteroid);
		auto dir = m_world.add<e::direction>(asteroid);
		auto ren = m_world.add<e::renderable>(asteroid);

		pos->pos = m::vec2(i * 10, 2);
		dir->angle = 20.f;
		util::createAsteroid(ren);
	}
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

void stateMenu::handleEvents()
{
}

void stateMenu::update(float deltaTime)
{
	m_world(deltaTime);
}

void stateMenu::render()
{
	// render everything to the fbo
	//fbo->begin();
	m_world();
	//fbo->end();

	//joy->render(cam);

	// render the contents of the fbo with the postfx
	//fbo->render();

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		LOGI("ast error %d", error);
	}
}

