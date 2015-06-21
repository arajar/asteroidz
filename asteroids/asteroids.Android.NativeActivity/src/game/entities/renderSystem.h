#pragma once

#include "entity.h"

namespace e
{
	// Render system:
	// Takes the position and direction of the entity and creates a transform matrix
	// Takes also the vbo and the shader of the object and renders the entity
	struct renderSystem : public ecs::system
	{
		renderSystem(ecs::world& world) : ecs::system(world), m_camera(nullptr) {}

		const gfx::camera* m_camera;

		void addCamera(const gfx::camera* camera) { m_camera = camera; }

		void operator()() const
		{
			for (auto& en : m_world.search<position, direction, renderable>())
			{
				const auto p = m_world.get<position>(en);
				const auto d = m_world.get<direction>(en);
				const auto r = m_world.get<renderable>(en);

				// take the current position and direction (angle) and create a transformation matrix
				const m::mat4 transform = m::mat4::translate(m::mat4(), m::vec3(p->pos)) * m::mat4::rotate(m::mat4(), d->angle, m::vec3(0, 0, 1));

				// future optimization: bind the shader only once to avoid binding and unbinding the same shader
				glBindBuffer(GL_ARRAY_BUFFER, r->vbo);
				
				glEnableVertexAttribArray(r->shader->attribute("vert"));
				glVertexAttribPointer(r->shader->attribute("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex), 0);

				glEnableVertexAttribArray(r->shader->attribute("color"));
				glVertexAttribPointer(r->shader->attribute("color"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex)
					, (void*)offsetof(gfx::vertex, color));

				r->shader->begin();
				r->shader->uniform("model", transform);
				r->shader->uniform("camera", m_camera->matrix());
				glDrawArrays(r->type, 0, r->numOfPolys);
				r->shader->end();

				glDisableVertexAttribArray(r->shader->attribute("vert"));
				glDisableVertexAttribArray(r->shader->attribute("color"));
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}
	};
}