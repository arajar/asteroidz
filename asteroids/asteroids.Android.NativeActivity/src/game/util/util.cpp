#include "util.h"

namespace util
{
	void createCircle(e::renderable* r, float radius)
	{
		r->shader = new gfx::shader;
		r->type = GL_LINE_LOOP;
		r->shader->vertex("circle.vs.glsl").pixel("circle.ps.glsl").link();

		const int sides = 36;

		gfx::vertex triangle_attributes[sides];

		for (int a = 0, index = 0; a < 360; a += 360 / sides, ++index)
		{
			float angle = math::toRad((float)a);
			triangle_attributes[index] = { {std::cos(angle) * radius, std::sin(angle) * radius, 0.f}, {1, 1, 1} };
		}

		r->numOfPolys = sizeof(triangle_attributes) / sizeof(gfx::vertex);

		// create the vbo and bind the attributes
		glGenBuffers(1, &r->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, r->vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_attributes), triangle_attributes, GL_STATIC_DRAW);

		glEnableVertexAttribArray(r->shader->attribute("vert"));
		glVertexAttribPointer(r->shader->attribute("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex), 0);
		glDisableVertexAttribArray(r->shader->attribute("vert"));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

#if defined DEBUG_COLLISIONS
	void createDebugCircle(e::debugRenderable * r, float radius)
	{
		r->shader = new gfx::shader;
		r->type = GL_LINE_LOOP;
		r->shader->vertex("circle.vs.glsl").pixel("circle.ps.glsl").link();

		const int sides = 18;

		gfx::vertex triangle_attributes[sides];

		for (int a = 0, index = 0; a < 360; a += 360 / sides, ++index)
		{
			float angle = math::radians((float)a);
			triangle_attributes[index] = { { math::cos(angle) * radius, math::sin(angle) * radius, 0.f },{ 1, 1, 1 } };
		}

		r->numOfPolys = sizeof(triangle_attributes) / sizeof(gfx::vertex);

		// create the vbo and bind the attributes
		glGenBuffers(1, &r->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, r->vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_attributes), triangle_attributes, GL_STATIC_DRAW);

		glEnableVertexAttribArray(r->shader->attribute("vert"));
		glVertexAttribPointer(r->shader->attribute("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex), 0);
		glDisableVertexAttribArray(r->shader->attribute("vert"));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
#endif

	void createAsteroid(e::renderable* r, float size)
	{
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_real_distribution<float> dist(-0.5, 0.5);
		std::uniform_real_distribution<float> sz(0.9f, 1.8f);

		// create a renderable component for the asteroid
		r->shader = new gfx::shader;
		r->type = GL_LINE_LOOP;
		r->shader->vertex("default.vs.glsl").pixel("default.ps.glsl").link();

		const float finalSize = sz(rng) * size;

		// basic more or less rounded asteroid, hand picked vertices that result in
		// better randomized shapes
		gfx::vertex triangle_attributes[] = {
			{ { 1.2f   * finalSize, 3.f    * finalSize, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { 2.75f  * finalSize, 1.9f   * finalSize, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { 3.7f   * finalSize, 0.5f   * finalSize, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { 3.4f   * finalSize, -1.3f  * finalSize, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { 2.4f   * finalSize, -2.65f * finalSize, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { 0.47f  * finalSize, -3.f   * finalSize, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { -1.2f  * finalSize, -2.8f  * finalSize, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { -2.3f  * finalSize, -2.3f  * finalSize, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { -3.1f  * finalSize, -0.42f * finalSize, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { -2.95f * finalSize, 0.44f  * finalSize, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { -2.05f * finalSize, 1.9f   * finalSize, 0.0 },{ 1.0, 1.0, 1.0 } },
			{ { -0.48f * finalSize, 3.f    * finalSize, 0.0 },{ 1.0, 1.0, 1.0 } },
		};
		
		r->numOfPolys = sizeof(triangle_attributes) / sizeof(gfx::vertex);

		// randomize a bit the shape of the asteroid
		for (size_t i = 0; i < sizeof(triangle_attributes->pos); i++)
		{
			auto vertex = triangle_attributes[i].pos;
			vertex[0] += (dist(rng)*finalSize);
			vertex[1] += (dist(rng)*finalSize);
		}

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

	void createShip(e::renderable* r, float size)
	{
		// create a renderable component for the ship
		r->shader = new gfx::shader;
		r->type = GL_LINE_LOOP;
		r->shader->vertex("default.vs.glsl").pixel("default.ps.glsl").link();

		gfx::vertex triangle_attributes[] = {
			{ { -5.3f  * size, 16.6f * size, 0.0 },{ 0.0 , 1.0, 1.0 } },
			{ { -16.3f * size, 0.f         , 0.0 },{ 0.87, 1.0, 1.0 } },
			{ { 0.f          , -11.f * size, 0.0 },{ 0.0 , 1.0, 1.0 } },
			{ { 16.3f  * size, 0.f         , 0.0 },{ 0.87, 1.0, 1.0 } },
			{ { 5.3f   * size, 16.6f * size, 0.0 },{ 0.0 , 1.0, 1.0 } },
			{ { 9.f    * size, 3.3f  * size, 0.0 },{ 0.87, 1.0, 1.0 } },
			{ { 0.f          , -0.9f * size, 0.0 },{ 0.87, 1.0, 1.0 } },
			{ { -9.0f  * size, 3.3f  * size, 0.0 },{ 0.87, 1.0, 1.0 } },
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

	void createMissile(e::renderable* r, float size)
	{
		if (r == nullptr)
		{
			r = new e::renderable;
		}

		r->shader = new gfx::shader;
		r->type = GL_LINE_LOOP;
		r->shader->vertex("default.vs.glsl").pixel("default.ps.glsl").link();

		gfx::vertex triangle_attributes[] = {
			{ { 0.f          , 1.0f  * size, 0.0 },{ 0.0, 1.0, 1.0 } },
			{ { 0.7f   * size, 0.0f        , 0.0 },{ 0.0, 1.0, 1.0 } },
			{ { 0.f          , -1.7f * size, 0.0 },{ 0.0, 1.0, 1.0 } },
			{ { -0.7f  * size, 0.0f        , 0.0 },{ 0.0, 1.0, 1.0 } },
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
