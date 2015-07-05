#pragma once

namespace m
{
	template<typename T>
	inline T pi();

	template<typename T>
	inline T toDeg(T angle);

	template<typename T>
	inline T toRad(T angle);

	template<typename T>
	mat4_type<T> perspective(T fov, T aspect, T near, T far);

	template<typename T>
	mat4_type<T> ortho(T left, T right, T bottom, T top);

	template<typename T>
	mat4_type<T> lookAt(const m::vec3_type<T>& eye, const m::vec3_type<T>& center, const m::vec3_type<T>& up);
}

#include "func.inl"