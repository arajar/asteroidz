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

void stateMenu::resume()
{
	math::mat4<float> m;

	m_shader = new gfx::shader;
	m_shader->vertex("default.vs").pixel("default.ps").link();

	struct attributes triangle_attributes[] = {
		{ { 0.0,  0.8, 0.0 },{ 1.0, 1.0, 0.0 } },
		{ { -0.8, -0.8, 0.0 },{ 0.0, 0.0, 1.0 } },
		{ { 0.8, -0.8, 0.0 },{ 1.0, 0.0, 0.0 } }
	};
	glGenBuffers(1, &vbo_triangle);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_attributes), triangle_attributes, GL_STATIC_DRAW);

	glEnableVertexAttribArray(m_shader->attribute("vert"));
	glVertexAttribPointer(m_shader->attribute("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(struct attributes), 0);

	glEnableVertexAttribArray(m_shader->attribute("color"));
	glVertexAttribPointer(m_shader->attribute("color"), 3, GL_FLOAT, GL_FALSE, sizeof(struct attributes)
		, (void*)offsetof(struct attributes, v_color));

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
	glDrawArrays(GL_TRIANGLES, 0, 3);
	m_shader->end();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
