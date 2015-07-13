#pragma once

//////////////////////////////////////////////////////////////////////////
// Small math library
//	Part of my public game framework available at:
//		http://github.com/arajar/math
//////////////////////////////////////////////////////////////////////////

#include <cmath>

// forward declarations
namespace math
{
	template<typename T> struct vec2_type;
	template<typename T> struct vec3_type;
	template<typename T> struct vec4_type;
	template<typename T> struct mat4_type;
}

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"

#include "func.h"
