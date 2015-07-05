#include "fbo.h"

namespace gfx
{
	void fbo::init(gfx::shader* shader)
	{
		if (shader == nullptr)
		{
			LOGE("ERROR: SHADER MUST NOT BE NULL!");
		}

		m_shader = shader;

		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		glGenTextures(1, &m_fboTexture);

		glBindTexture(GL_TEXTURE_2D, m_fboTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_resolution.x, m_resolution.y, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glGenRenderbuffers(1, &m_depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_resolution.x, m_resolution.y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		switch (status)
		{
		case GL_FRAMEBUFFER_COMPLETE:
			LOGE("GL_FRAMEBUFFER_COMPLETE");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			LOGE("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			LOGE("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS:
			LOGE("GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS");
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			LOGE("GL_FRAMEBUFFER_UNSUPPORTED");
			break;
		default:
			LOGE("error");
			break;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		GLfloat fbo_vertices[] = {
			-1, -1,
			1, -1,
			-1,  1,
			1,  1,
		};

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(fbo_vertices), fbo_vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void fbo::begin()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	}

	void fbo::end()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void fbo::render()
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBindTexture(GL_TEXTURE_2D, m_fboTexture);
		m_shader->begin();

		glEnableVertexAttribArray(m_shader->attribute("vert"));
		glVertexAttribPointer(m_shader->attribute("vert"), 2, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		glDisableVertexAttribArray(m_shader->attribute("vert"));

		m_shader->end();
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}