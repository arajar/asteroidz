#pragma once
#include "../entities/entity.h"

class stateMenu : public states::state
{
public:
	stateMenu(const glm::vec2& screenSize) : m_screenSize(screenSize) {}

public:
	// Inherited via state
	virtual void start() override;
	virtual void resume() override;
	virtual void suspend() override;
	virtual void end() override;

public:
	virtual void handleEvents(const input::TouchEvent& type) override;
	virtual void update(float deltaTime) override;
	virtual void render() override;

protected:
	ecs::entity		m_ship;
	
private:
	ecs::world		m_world;
	const glm::vec2	m_screenSize;
};