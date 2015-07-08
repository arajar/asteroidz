#pragma once
#include "../entities/entity.h"

class stateMenu : public states::state
{
public:
	stateMenu(const math::vec2& screenSize) : m_screenSize(screenSize) {}

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
	gfx::texturedBox	m_background;
	math::mat4			m_projection;

private:
	const math::vec2		m_screenSize;
};