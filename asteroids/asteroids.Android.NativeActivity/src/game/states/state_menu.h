#pragma once
#include "../entities/entity.h"

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
	e::renderable createAsteroid();

private:
	gfx::shader* m_shader;
};