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

		void operator()() const
		{
			//auto projection = m::ortho<float>(0.0f, 800.0f, 600.0f, 0.0f);
			glm::mat4 projection = glm::ortho(0.0f, 1804.f, 1080.f, 0.0f, -1.f, 1000.f);

			//glm::mat4 projection = glm::perspective(45.f, 1804.f / 1080.f, 0.001f, 1000000.f);
			projection *= glm::translate(glm::mat4(), glm::vec3(0, 0, -100));
			//projection *= glm::lookAt(glm::vec3(1804.f/2.f, 0, 1804/2.f), glm::vec3(0), glm::vec3(0, 1, 0));

			for (auto& en : m_world.search<position, renderable>())
			{
				const auto p = m_world.get<position>(en);
				const auto r = m_world.get<renderable>(en);

				// take the current position and direction (angle) and create a transformation matrix
				//const m::mat4 transform = m::mat4::translate(m::mat4(), m::vec3(p->pos));
				glm::mat4 transform = glm::translate(glm::mat4(), glm::vec3(p->pos, 0.f)) * glm::scale(glm::mat4(), glm::vec3(-1));

				const auto localRot = m_world.get<localRotation>(en);
				const auto dir = m_world.get<direction>(en);
				if (localRot)
				{
					transform *= glm::rotate(glm::mat4(), localRot->rotation, glm::vec3(0, 0, 1));
				}

				if (dir)
				{
					transform *= glm::rotate(glm::mat4(), dir->angle, glm::vec3(0, 0, 1));
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

			for (auto& en : m_world.search<missileArray>())
			{
				const auto m = m_world.get<missileArray>(en);
				const auto r = m->ren;

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
					glm::mat4 transform = glm::translate(glm::mat4(), glm::vec3(missile.pos, 0.f)) * glm::scale(glm::mat4(), glm::vec3(-1));
					transform *= glm::rotate(glm::mat4(), missile.dir, glm::vec3(0, 0, 1));

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