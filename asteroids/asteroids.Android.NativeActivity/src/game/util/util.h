#pragma once
#include <random>

namespace util
{
	void createCircle(e::renderable* r, float radius);
	
#if defined DEBUG_COLLISIONS
	void createDebugCircle(e::debugRenderable* r, float radius);
#endif

	void createAsteroid(e::renderable* r, float size);
	void createShip(e::renderable* r, float size);
	void createMissile(e::renderable* r, float size);
}
