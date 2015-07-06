#pragma once

namespace math
{
	template<typename T>
	mat4_type<T> mat4_type<T>::inverse(const mat4_type<T>& m)
	{
		T c00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T c02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		T c03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		T c04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T c06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T c07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		T c08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T c10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		T c11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		T c12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T c14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		T c15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		T c16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T c18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		T c19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		T c20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		T c22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		T c23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		vec4_type<T> f0(c00, c00, c02, c03);
		vec4_type<T> f1(c04, c04, c06, c07);
		vec4_type<T> f2(c08, c08, c10, c11);
		vec4_type<T> f3(c12, c12, c14, c15);
		vec4_type<T> f4(c16, c16, c18, c19);
		vec4_type<T> f5(c20, c20, c22, c23);

		vec4_type<T> v0(m[1][0], m[0][0], m[0][0], m[0][0]);
		vec4_type<T> v1(m[1][1], m[0][1], m[0][1], m[0][1]);
		vec4_type<T> v2(m[1][2], m[0][2], m[0][2], m[0][2]);
		vec4_type<T> v3(m[1][3], m[0][3], m[0][3], m[0][3]);

		vec4_type<T> inv0(v1 * f0 - v2 * f1 + v3 * f2);
		vec4_type<T> inv1(v0 * f0 - v2 * f3 + v3 * f4);
		vec4_type<T> inv2(v0 * f1 - v1 * f3 + v3 * f5);
		vec4_type<T> inv3(v0 * f2 - v1 * f4 + v2 * f5);

		vec4_type<T> signA(+1, -1, +1, -1);
		vec4_type<T> signB(-1, +1, -1, +1);
		mat4_type<T> inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

		vec4_type<T> row0(inverse[0][0], inverse[1][0], inverse[2][0], inverse[3][0]);

		vec4_type<T> dot0(m[0] * row0);
		T dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);

		T oneOverDeterminant = static_cast<T>(1) / dot1;

		return inverse * oneOverDeterminant;
	}

	template<typename T>
	mat4_type<T> translate(const mat4_type<T>& m, const vec2_type<T>& v)
	{
		return translate(m, vec3_type<T>(v));
	}
	
	template<typename T>
	mat4_type<T> mat4_type<T>::translate(const mat4_type<T>& m, const vec3_type<T>& v)
	{
		mat4_type<T> res = m;
		res[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
		return res;
	}

	template<typename T>
	mat4_type<T> mat4_type<T>::rotate(const mat4_type<T>& m, T angle, const vec3_type<T>& v)
	{
		const T a = angle;
		const T c = std::cos(a);
		const T s = std::sin(a);

		auto axis(normalize(v));
		auto temp((T(1) - c) * axis);

		mat4_type<T> rot;
		rot[0][0] = c + temp[0] * axis[0];
		rot[0][1] = 0 + temp[0] * axis[1] + s * axis[2];
		rot[0][2] = 0 + temp[0] * axis[2] - s * axis[1];

		rot[1][0] = 0 + temp[1] * axis[0] - s * axis[2];
		rot[1][1] = c + temp[1] * axis[1];
		rot[1][2] = 0 + temp[1] * axis[2] + s * axis[0];

		rot[2][0] = 0 + temp[2] * axis[0] + s * axis[1];
		rot[2][1] = 0 + temp[2] * axis[1] - s * axis[0];
		rot[2][2] = c + temp[2] * axis[2];

		mat4_type<T> res;
		res[0] = m[0] * rot[0][0] + m[1] * rot[0][1] + m[2] * rot[0][2];
		res[1] = m[0] * rot[1][0] + m[1] * rot[1][1] + m[2] * rot[1][2];
		res[2] = m[0] * rot[2][0] + m[1] * rot[2][1] + m[2] * rot[2][2];
		res[3] = m[3];
		return res;
	}

	template<typename T>
	mat4_type<T> mat4_type<T>::scale(const mat4_type<T>& m, const vec3_type<T>& v)
	{
		mat4_type<T> res;
		res[0] = m[0] * v[0];
		res[1] = m[1] * v[1];
		res[2] = m[2] * v[2];
		res[3] = m[3];
		return res;
	}
}