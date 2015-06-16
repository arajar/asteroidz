#include "state_menu.h"


#define BUFFER_OFFSET(i) ((char *)NULL + (i))

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

void stateMenu::resume()
{
	m_shader = new gfx::shader;
	m_shader->vertex("default.vs.glsl").pixel("default.ps.glsl").link();

	struct attributes triangle_attributes[] = {
		{ { 0.0, 0.8, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { -0.6, -0.8, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 0.0, 0.0, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 0.0, 0.8, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 0.6, -0.8, 0.0 },{ 1.0, 1.0, 1.0 } },
		{ { 0.0, 0.0, 0.0 },{ 1.0, 1.0, 1.0 } },
	};
	glGenBuffers(1, &vbo_triangle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_attributes), triangle_attributes, GL_STATIC_DRAW);

	glEnableVertexAttribArray(m_shader->attribute("vert"));
	glVertexAttribPointer(m_shader->attribute("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(struct attributes), 0);

	glEnableVertexAttribArray(m_shader->attribute("color"));
	glVertexAttribPointer(m_shader->attribute("color"), 3, GL_FLOAT, GL_FALSE, sizeof(struct attributes)
		, (void*)offsetof(struct attributes, v_color));

	cam.setPosition(m::vec3(0, 0, 17));
	cam.setViewportAspectRatio(1804.f / (float)1080.f);

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
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	m_shader->begin();

	m::mat4 model = m::mat4::translate(m::mat4(), m::vec3(10, 0, 0));

	m_shader->uniform("camera", cam.matrix());
	m_shader->uniform("model", model);

	glDrawArrays(GL_LINES, 0, 6);
	m_shader->end();
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		int a = 4234;
		a++;
	}
}
