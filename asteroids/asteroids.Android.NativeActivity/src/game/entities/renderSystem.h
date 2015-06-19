#pragma once

#include "entity.h"

namespace e
{
	// Render system:
	// Takes the position and direction of the entity and creates a transform matrix
	// Takes also the vbo and the shader of the object and renders the entity
	struct renderSystem : public ecs::system
	{
		renderSystem(ecs::world& world, gfx::camera* camera) : ecs::system(world), m_camera(camera) {}

		const gfx::camera* m_camera;

		void operator()() const
		{
			for (auto& en : m_world.search<position, direction, renderable>())
			{
				const auto p = m_world.get<position>(en);
				const auto d = m_world.get<direction>(en);
				const auto r = m_world.get<renderable>(en);

				// take the current position and direction (angle) and create a transformation matrix
				const m::mat4 transform = m::mat4::translate(m::mat4(), p->pos) * m::mat4::rotate(m::mat4(), d->angle, m::vec3(0, 1, 0));

				// future optimization: bind the shader only once to avoid binding and unbinding the same shader
				glBindBuffer(GL_ARRAY_BUFFER, r->vbo);
				r->shader->begin();
				r->shader->uniform("model", transform);
				r->shader->uniform("camera", m_camera->matrix());
				glDrawArrays(GL_TRIANGLES, 0, r->numOfPolys);
				r->shader->end();
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}
	};
}