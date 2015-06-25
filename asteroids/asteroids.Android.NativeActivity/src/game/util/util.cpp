#include "util.h"

namespace util
{
	void createCircle(e::renderable* r)
	{
		r->shader = new gfx::shader;
		r->type = GL_TRIANGLE_STRIP;
		r->shader->vertex("circle.vs.glsl").pixel("circle.ps.glsl").link();

		gfx::vertex triangle_attributes[] = {
			{ { -1.f, -1.f, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { 1.f , -1.f, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { -1.f,  1.f, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { 1.f ,  1.f, 0.0 },{ 1.0, 1.0, 1.0 } },
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

	void createAsteroid(e::renderable* r)
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
			{ { -3.1f   * size, -0.42f * size, 0.0 },{ 1.0, 1.0, 1.0 } },
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

	void createShip(e::renderable* r)
	{
		// create a renderable component for the ship
		r->shader = new gfx::shader;
		r->type = GL_LINE_LOOP;
		r->shader->vertex("default.vs.glsl").pixel("default.ps.glsl").link();

		gfx::vertex triangle_attributes[] = {
			{ { -5.3f, 16.6f , 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { -16.3f, 0.f   , 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { 0.f   , -11.f , 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { 16.3f , 0.f   , 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { 5.3f , 16.6f , 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { 9.f  , 3.3f , 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { 0.f   , -0.9f, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { -9.0f , 3.3f , 0.0 },{ 1.0, 1.0, 1.0 } },
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
}
