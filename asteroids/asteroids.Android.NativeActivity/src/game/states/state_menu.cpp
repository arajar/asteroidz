#include "state_menu.h"
#include <random>

#include "../entities/renderSystem.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

gfx::camera cam;
gfx::fbo* fbo;

void stateMenu::start()
{
	cam.setPosition(m::vec3(10, 0, 30));
	cam.setViewportAspectRatio(1804.f / (float)1080.f);

	fbo = new gfx::fbo(m::vec2(1804.f, 1080.f));
	auto sh = new gfx::shader;
	sh->vertex("default.vs.glsl").pixel("default.ps.glsl").link();
	fbo->init(sh);

	auto render = m_world.add<e::renderSystem>();
	render->addCamera(&cam);

	auto ship = m_world.createEntity();

	auto pos = m_world.add<e::position>(ship);
	auto dir = m_world.add<e::direction>(ship);
	auto ren = m_world.add<e::renderable>(ship);

	pos->pos = m::vec2(0, 0);
	dir->angle = 0;
	createShip(ren);

	for (size_t i = 0; i < 10; i++)
	{
		auto asteroid = m_world.createEntity();

		auto pos = m_world.add<e::position>(asteroid);
		auto dir = m_world.add<e::direction>(asteroid);
		auto ren = m_world.add<e::renderable>(asteroid);

		pos->pos = m::vec2(i * 10, 2);
		dir->angle = 20.f;
		createAsteroid(ren);
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
	fbo->begin();
	m_world();
	fbo->end();

	// render the contents of the fbo with the postfx
	fbo->render();

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		LOGI("ast error %d", error);
	}
}

void stateMenu::createAsteroid(e::renderable* r)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	static int seed = 10;
	rng.seed(++seed);
	std::uniform_real_distribution<float> dist(-0.5, 0.5);
	std::uniform_real_distribution<float> sz(0.2, 1.f);

	// create a renderable component for the asteroid
	r->shader = new gfx::shader;
	r->type = GL_LINE_LOOP;
	r->shader->vertex("default.vs.glsl").pixel("default.ps.glsl").link();

	const float size = sz(rng);

	// basic more or less rounded asteroid
	gfx::vertex triangle_attributes[] = {
		{ { 1.2f   * size, 3.f    * size, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 2.75f  * size, 1.9f   * size, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 3.7f   * size, 0.5f   * size, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 3.4f   * size, -1.3f  * size, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 2.4f   * size, -2.65f * size, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 0.47f  * size, -3.f   * size, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -1.2f  * size, -2.8f  * size, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -2.3f  * size, -2.3f  * size, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ {-3.1f   * size, -0.42f * size, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -2.95f * size, 0.44f  * size, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -2.05f * size, 1.9f   * size, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -0.48f * size, 3.f    * size, 0.0 },{ 1.0, 1.0, 1.0 } },
	};

	r->numOfPolys = sizeof(triangle_attributes) / sizeof(gfx::vertex);

	// randomize a bit the shape of the asteroid
	for (size_t i = 0; i < sizeof(triangle_attributes->pos); i++)
	{
		auto vertex = triangle_attributes[i].pos;
		vertex[0] += (dist(rng)*size);
		vertex[1] += (dist(rng)*size);

		LOGI("ast (%0.2f, %0.2f)", vertex[0], vertex[1]);
	}

	LOGI("end");
	// create the vbo and bind the attributes
	glGenBuffers(1, &r->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, r->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_attributes), triangle_attributes, GL_STATIC_DRAW);

	glEnableVertexAttribArray(r->shader->attribute("vert"));
	glVertexAttribPointer(r->shader->attribute("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex), 0);

	glEnableVertexAttribArray(r->shader->attribute("color"));
	glVertexAttribPointer(r->shader->attribute("color"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex),
		(void*)offsetof(gfx::vertex, color));

	glDisableVertexAttribArray(r->shader->attribute("vert"));
	glDisableVertexAttribArray(r->shader->attribute("color"));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void stateMenu::createShip(e::renderable* r)
{
	// create a renderable component for the ship
	r->shader = new gfx::shader;
	r->type = GL_LINE_LOOP;
	r->shader->vertex("default.vs.glsl").pixel("default.ps.glsl").link();

	gfx::vertex triangle_attributes[] = {
		{ { -0.53f, 1.66f , 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -1.63f, 0.f   , 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 0.f   , -1.1f , 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 1.63f , 0.f   , 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 0.53f , 1.66f , 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 0.9f  , 0.33f , 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 0.f   , -0.09f, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -0.9f , 0.33f , 0.0 },{ 1.0, 1.0, 1.0 } },
	};

	r->numOfPolys = sizeof(triangle_attributes) / sizeof(gfx::vertex);

	// create the vbo and bind the attributes
	glGenBuffers(1, &r->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, r->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_attributes), triangle_attributes, GL_STATIC_DRAW);

	glEnableVertexAttribArray(r->shader->attribute("vert"));
	glVertexAttribPointer(r->shader->attribute("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex), 0);

	glEnableVertexAttribArray(r->shader->attribute("color"));
	glVertexAttribPointer(r->shader->attribute("color"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex),
		(void*)offsetof(gfx::vertex, color));

	glDisableVertexAttribArray(r->shader->attribute("vert"));
	glDisableVertexAttribArray(r->shader->attribute("color"));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
