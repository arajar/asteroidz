#include "state_menu.h"
#include <random>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "asteroids.NativeActivity", __VA_ARGS__))

void stateMenu::start()
{
}

struct attributes {
	GLfloat coord3d[3];
	GLfloat v_color[3];
};

GLuint vbo_triangle;
GLint attribute_coord3d, attribute_v_color;
GLint uniform_m_transform;

gfx::camera cam;

std::vector<e::renderable> asteroids;
std::vector<m::vec2> positions;

void stateMenu::resume()
{
	m_shader = new gfx::shader;
	m_shader->vertex("default.vs.glsl").pixel("default.ps.glsl").link();

	struct attributes triangle_attributes[] = {
		{ { 0.0, 0.8, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -0.6, -0.8, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 0.0, -0.4, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 0.0, 0.8, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 0.6, -0.8, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 0.0, -0.4, 0.0 },{ 1.0, 1.0, 1.0 } },
	};
	glGenBuffers(1, &vbo_triangle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_attributes), triangle_attributes, GL_STATIC_DRAW);

	glEnableVertexAttribArray(m_shader->attribute("vert"));
	glVertexAttribPointer(m_shader->attribute("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(struct attributes), 0);

	glEnableVertexAttribArray(m_shader->attribute("color"));
	glVertexAttribPointer(m_shader->attribute("color"), 3, GL_FLOAT, GL_FALSE, sizeof(struct attributes)
		, (void*)offsetof(struct attributes, v_color));

	cam.setPosition(m::vec3(10, 0, 30));
	cam.setViewportAspectRatio(1804.f / (float)1080.f);

	int y = 0;
	for (int i = 0; i < 10; ++i)
	{
		if (i >= 5)
		{
			y = 20;
		}

		asteroids.push_back(createAsteroid());
		positions.push_back(m::vec2(i*15, y));
	}

	//glDisableVertexAttribArray(m_shader->attribute("vert"));
	//glDisableVertexAttribArray(m_shader->attribute("color"));

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
}

void stateMenu::render()
{
	//for (int i = 0; i < asteroids.size(); ++i)
	{
		//LOGI("ast %d", i);
		const auto& asteroid = asteroids[0];
		const auto& pos = positions[0];
		
		glBindBuffer(GL_ARRAY_BUFFER, 2);
		//LOGI("ast vbo %d", asteroid.vbo);
		m::mat4 m = m::mat4::translate(m::mat4(), m::vec3(pos.x, pos.y, 0)) * m::mat4::scale(m::mat4(), m::vec3(0.5));
		asteroid.shader->begin();
		asteroid.shader->uniform("camera", cam.matrix());
		asteroid.shader->uniform("model", m);
		glDrawArrays(GL_LINE_LOOP, 0, asteroid.numOfPolys);
		asteroid.shader->end();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	m_shader->begin();

	m::mat4 model = m::mat4::translate(m::mat4(), m::vec3(10, 0, 0));

	m_shader->uniform("camera", cam.matrix());
	m_shader->uniform("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	m_shader->end();
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	{
		//LOGI("ast %d", i);
		const auto& asteroid = asteroids[1];
		const auto& pos = positions[1];

		glBindBuffer(GL_ARRAY_BUFFER, 4);
		//LOGI("ast vbo %d", asteroid.vbo);
		m::mat4 m = m::mat4::translate(m::mat4(), m::vec3(pos.x, pos.y, 0)) * m::mat4::scale(m::mat4(), m::vec3(0.5));
		asteroid.shader->begin();
		asteroid.shader->uniform("camera", cam.matrix());
		asteroid.shader->uniform("model", m);
		glDrawArrays(GL_LINE_LOOP, 0, asteroid.numOfPolys);
		asteroid.shader->end();
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		LOGI("ast error %d", error);
	}
}

e::renderable stateMenu::createAsteroid()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	static int seed = 10;
	rng.seed(++seed);
	std::uniform_real_distribution<float> dist(-3, 3);

	// basic more or less rounded asteroid
	struct attributes triangle_attributes[] = {
		{ { 2.4, 6, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 5.5, 3.8, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 7.4, 1, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 6.8, -2.6, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 4.8, -5.3, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 0.94, -6, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -2.4, -5.6, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -4.6, -4.6, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ {-6.2, -2.1, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -5.9, 0.88, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -4.1, 3.8, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -0.96, 6, 0.0 },{ 1.0, 1.0, 1.0 } },
	};

	int numOfVertices = sizeof(triangle_attributes);
	LOGI("number: %d", numOfVertices);
	// randomize a bit the shape of the asteroid
	for (size_t i = 0; i < sizeof(triangle_attributes->coord3d); i++)
	{
		auto vertex = triangle_attributes[i].coord3d;
		vertex[0] += dist(rng);
		vertex[1] += dist(rng);

		LOGI("ast (%0.2f, %0.2f)", vertex[0], vertex[1]);
	}

	LOGI("end");
	// create the vbo and bind the attributes
	GLuint vbo = -1;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_attributes), triangle_attributes, GL_STATIC_DRAW);

	glEnableVertexAttribArray(m_shader->attribute("vert"));
	glVertexAttribPointer(m_shader->attribute("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(struct attributes), 0);

	glEnableVertexAttribArray(m_shader->attribute("color"));
	glVertexAttribPointer(m_shader->attribute("color"), 3, GL_FLOAT, GL_FALSE, sizeof(struct attributes), (void*)offsetof(struct attributes, v_color));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// create a renderable component for the asteroid
	e::renderable r;
	r.vbo = vbo;
	r.numOfPolys = sizeof(triangle_attributes->coord3d);
	r.shader = new gfx::shader;
	r.shader->vertex("default.vs.glsl").pixel("default.ps.glsl").link();

	return r;
}
