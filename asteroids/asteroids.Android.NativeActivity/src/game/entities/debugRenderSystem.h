#pragma once

#include "entity.h"

#if defined DEBUG_COLLISIONS
namespace e
{
	// Render system:
	// Takes the position and direction of the entity and creates a transform matrix
	// Takes also the vbo and the shader of the object and renders the entity
	struct debugRenderSystem : public ecs::system
	{
		debugRenderSystem(ecs::world& world) : ecs::system(world) {}

		void operator()() const
		{
			glm::mat4 projection = glm::ortho(0.0f, 1804.f, 1080.f, 0.0f, -1.f, 1000.f);
			projection *= glm::translate(glm::mat4(), glm::vec3(0, 0, -100));

			for (auto& en : m_world.search<position, debugRenderable>())
			{
				const auto p = m_world.get<position>(en);
				const auto r = m_world.get<debugRenderable>(en);

				// take the current position and direction (angle) and create a transformation matrix
				glm::mat4 transform = glm::translate(glm::mat4(), glm::vec3(p->pos, 0.f)) * glm::scale(glm::mat4(), glm::vec3(-1));

				// future optimization: bind the shader only once to avoid binding and unbinding the same shader
				glBindBuffer(GL_ARRAY_BUFFER, r->vbo);

				glEnableVertexAttribArray(r->shader->attribute("vert"));
				glVertexAttribPointer(r->shader->attribute("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(gfx::vertex), 0);

				r->shader->begin();
				r->shader->uniform("model", transform);
				r->shader->uniform("camera", projection);
				r->shader->uniform("finalColor", glm::vec4(1.f));
				glDrawArrays(r->type, 0, r->numOfPolys);
				r->shader->end();

				glDisableVertexAttribArray(r->shader->attribute("vert"));
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}
	};
}
#endif
