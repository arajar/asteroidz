#pragma once
#include "../entities/entity.h"

class stateMenu : public states::state
{
public:
	stateMenu(const m::vec2& screenSize) : m_screenSize(screenSize) {}

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
	ecs::world m_world;
	const m::vec2 m_screenSize;
};