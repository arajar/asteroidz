#pragma once

namespace math
{
	template<typename T>
	inline T pi();

	template<typename T>
	inline T toDeg(T angle);

	template<typename T>
	inline T toRad(T angle);

	template<typename T>
	float length(const vec2_type<T>& v);

	template<typename T>
	float length(const vec3_type<T>& v);

	template<typename T>
	float length(const vec4_type<T>& v);

	template<typename T>
	float dot(const vec2_type<T>& a, const vec2_type<T>& b);

	template<typename T>
	float dot(const vec3_type<T>& a, const vec3_type<T>& b);

	template<typename T>
	float dot(const vec4_type<T>& a, const vec4_type<T>& b);

	template<typename T>
	T clamp(T val, T min, T max);

	template<typename T>
	vec3_type<T> cross(const vec3_type<T>& a, const vec3_type<T>& b);

	template<typename T>
	vec2_type<T> normalize(const vec2_type<T>& v);

	template<typename T>
	vec3_type<T> normalize(const vec3_type<T>& v);

	template<typename T>
	vec4_type<T> normalize(const vec4_type<T>& v);

	template<typename T>
	mat4_type<T> perspective(T fov, T aspect, T near, T far);

	template<typename T>
	mat4_type<T> ortho(T left, T right, T bottom, T top, T near, T far);

	template<typename T>
	mat4_type<T> lookAt(const vec3_type<T>& eye, const vec3_type<T>& center, const vec3_type<T>& up);

	template<typename T>
	mat4_type<T> inverse(const mat4_type<T>& m);
	
	template<typename T>
	mat4_type<T> translate(const mat4_type<T>& m, const vec3_type<T>& v);
	
	template<typename T>
	mat4_type<T> rotate(const mat4_type<T>& m, T angle, const vec3_type<T>& v);
	
	template<typename T>
	mat4_type<T> scale(const mat4_type<T>& m, const vec3_type<T>& v);
	
	template<typename T>
	const T* toGl(const vec2_type<T>& v);

	template<typename T>
	const T* toGl(const vec3_type<T>& v);

	template<typename T>
	const T* toGl(const vec4_type<T>& v);

	template<typename T>
	const T* toGl(const mat4_type<T>& m);
}

#include "func.inl"