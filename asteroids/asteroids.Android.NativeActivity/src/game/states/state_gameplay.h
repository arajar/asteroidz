#pragma once
#include "../entities/entity.h"

class stateGameplay : public states::state
{
public:
	stateGameplay(const math::vec2& screenSize) : m_screenSize(screenSize) {}

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
	ecs::entity				m_ship;
	const e::entityType*	m_shipType = nullptr;
	math::mat4				m_projection;

	util::tweener<float>	m_timer;

	input::virtualJoystick	m_leftJoy;
	input::virtualJoystick	m_rightJoy;
	gfx::texturedBox		background;
private:
	ecs::world				m_world;
	const math::vec2		m_screenSize;
};