#pragma once

#include "entity.h"

namespace e
{
	// Render system:
	// Takes the position and direction of the entity and creates a transform matrix
	// Takes also the vbo and the shader of the object and renders the entity
	struct renderSystem : public ecs::system
	{
		renderSystem(ecs::world& world) : ecs::system(world) {}

		math::vec2 m_size;

		void setWindowSize(const math::vec2& size) { m_size = size; }

		void operator()() const
		{
			// future optimization:
			// - sort the entities by shader and bind the shader only once
			// - create a batching system to batch render all the entities
			math::mat4 projection = math::ortho(0.0f, m_size.x, m_size.y, 0.0f, -1.f, 1000.f);
			projection *= math::translate(math::mat4(), math::vec3(0, 0, -100));

			for (auto& en : m_world.search<position, renderable>())
			{
				const auto& p = m_world.get<position>(en);
				const auto& r = m_world.get<renderable>(en);

				// take the current position and direction (angle) and create a transformation matrix
				math::mat4 transform = math::translate(math::mat4(), math::vec3(p->pos.x, p->pos.y, 0.f));
				transform *= math::scale(math::mat4(), math::vec3(-1));

				const auto& localRot = m_world.get<localRotation>(en);
				const auto& dir = m_world.get<direction>(en);
				if (localRot)
				{
					// if the entity has a local rotation matrix, apply the rotation
					transform *= math::rotate(math::mat4(), localRot->rotation, math::vec3(0, 0, 1));
				}

				if (dir)
				{
					// if the entity has a direction, apply the direction
					transform *= math::rotate(math::mat4(), dir->angle, math::vec3(0, 0, 1));
				}

				// future optimization: bind the shader only once to avoid binding and unbinding the same shader
				glBindBuffer(GL_ARRAY_BUFFER, r->vbo);

				glEnableVertexAttribArray(r->shader->attribute("vert"));
				glVertexAttribPointer(r->shader->attribute("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex), 0);

				glEnableVertexAttribArray(r->shader->attribute("color"));
				glVertexAttribPointer(r->shader->attribute("color"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex)
					, (void*)offsetof(gfx::vertex, color));

				r->shader->begin();
				r->shader->uniform("model", transform);
				r->shader->uniform("camera", projection);
				glDrawArrays(r->type, 0, r->numOfPolys);
				r->shader->end();

				glDisableVertexAttribArray(r->shader->attribute("vert"));
				glDisableVertexAttribArray(r->shader->attribute("color"));
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			// render the missiles
			for (auto& en : m_world.search<missileArray>())
			{
				const auto& m = m_world.get<missileArray>(en);
				const auto& r = m->ren;

				glBindBuffer(GL_ARRAY_BUFFER, r.vbo);

				glEnableVertexAttribArray(r.shader->attribute("vert"));
				glVertexAttribPointer(r.shader->attribute("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex), 0);

				glEnableVertexAttribArray(r.shader->attribute("color"));
				glVertexAttribPointer(r.shader->attribute("color"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex)
					, (void*)offsetof(gfx::vertex, color));

				r.shader->begin();

				for (size_t i = 0; i < m->missiles.size(); ++i)
				{
					auto missile = m->missiles[i];
					math::mat4 transform = math::translate(math::mat4(), math::vec3(missile.pos.x, missile.pos.y, 0.f));
					transform *= math::scale(math::mat4(), math::vec3(-1));
					transform *= math::rotate(math::mat4(), missile.dir, math::vec3(0, 0, 1));

					r.shader->uniform("model", transform);
					r.shader->uniform("camera", projection);
					glDrawArrays(r.type, 0, r.numOfPolys);
				}

				r.shader->end();

				glDisableVertexAttribArray(r.shader->attribute("vert"));
				glDisableVertexAttribArray(r.shader->attribute("color"));
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}
	};
}