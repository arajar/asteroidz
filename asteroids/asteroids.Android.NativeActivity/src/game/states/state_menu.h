#pragma once

#include "../../framework/graphics/shader.h"

class stateMenu : public states::state
{
public:
	// Inherited via state
	virtual void start() override;
	virtual void resume() override;
	virtual void suspend() override;
	virtual void end() override;

public:
	virtual void handleEvents() override;
	virtual void update(float deltaTime) override;
	virtual void render() override;

private:
	gfx::shader* m_shader;
	GLuint m_vertexBuffer;
	GLuint m_indexBuffer;

	GLubyte m_indices[3];
};