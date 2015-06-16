#pragma once
#include <cmath>

namespace m
{
	template<typename T>
	mat4x4<T>& mat4x4<T>::transpose()
	{
		std::swap(m01, m10); std::swap(m02, m20); std::swap(m03, m30);
		std::swap(m12, m21); std::swap(m13, m31); std::swap(m23, m32);
		return *this;
	}

	template<typename T>
	mat4x4<T>& mat4x4<T>::rotateX(T degrees)
	{
		T radians = toRad<T>(degrees);
		T s = std::sin(radians);
		T c = std::cos(radians);
		T t01 = m01, t02 = m02;
		T t11 = m11, t12 = m12;
		T t21 = m21, t22 = m22;
		T t31 = m31, t32 = m32;
		m01 = c * t01 - s * t02;
		m02 = c * t02 + s * t01;
		m11 = c * t11 - s * t12;
		m12 = c * t12 + s * t11;
		m21 = c * t21 - s * t22;
		m22 = c * t22 + s * t21;
		m31 = c * t31 - s * t32;
		m32 = c * t32 + s * t31;
		return *this;
	}

	template<typename T>
	mat4x4<T>& mat4x4<T>::rotateY(T degrees)
	{
		T radians = toRad<T>(degrees);
		T s = std::sin(radians);
		T c = std::cos(radians);
		T t02 = m02, t00 = m00;
		T t12 = m12, t10 = m10;
		T t22 = m22, t20 = m20;
		T t32 = m32, t30 = m30;
		m02 = c * t02 - s * t00;
		m00 = c * t00 + s * t02;
		m12 = c * t12 - s * t10;
		m10 = c * t10 + s * t12;
		m22 = c * t22 - s * t20;
		m20 = c * t20 + s * t22;
		m32 = c * t32 - s * t30;
		m30 = c * t30 + s * t32;
		return *this;
	}

	template<typename T>
	mat4x4<T>& mat4x4<T>::rotateZ(T degrees)
	{
		T radians = toRad<T>(degrees);
		T s = std::sin(radians);
		T c = std::cos(radians);
		T t00 = m00, t01 = m01;
		T t10 = m10, t11 = m11;
		T t20 = m20, t21 = m21;
		T t30 = m30, t31 = m31;
		m00 = c * t00 - s * t01;
		m01 = c * t01 + s * t00;
		m10 = c * t10 - s * t11;
		m11 = c * t11 + s * t10;
		m20 = c * t20 - s * t21;
		m21 = c * t21 + s * t20;
		m30 = c * t30 - s * t31;
		m31 = c * t31 + s * t30;
		return *this;
	}

	template<typename T>
	mat4x4<T>& mat4x4<T>::rotate(T degrees, const vec3<T>& axis)
	{
		T radians = toRad<T>(degrees);
		T d = axis.length();
		T s = std::sin(radians);
		T c = std::cos(radians);
		T t = 1 - c;
		auto a = axis / d;
		return *this *= mat4x4(
			axis.x*axis.x*t + c, axis.x*axis.y*t - axis.z*s, axis.x*axis.z*t + axis.y*s, 0,
			axis.y*axis.x*t + axis.z*s, axis.y*axis.y*t + c, axis.y*axis.z*t - axis.x*s, 0,
			axis.z*axis.x*t - axis.y*s, axis.z*axis.y*t + axis.x*s, axis.z*axis.z*t + c, 0,
			0, 0, 0, 1);
	}

	template<typename T>
	mat4x4<T>& mat4x4<T>::scale(const vec3<T>& s)
	{
		m00 *= s.x; m01 *= s.y; m02 *= s.z;
		m10 *= s.x; m11 *= s.y; m12 *= s.z;
		m20 *= s.x; m21 *= s.y; m22 *= s.z;
		m30 *= s.x; m31 *= s.y; m32 *= s.z;
		return *this;
	}

	template<typename T>
	mat4x4<T>& mat4x4<T>::ortho(T l, T r, T b, T t, T n, T f)
	{
		return *this *= mat4x4(
			2 / (r - l), 0, 0, (r + l) / (l - r),
			0, 2 / (t - b), 0, (t + b) / (b - t),
			0, 0, 2 / (n - f), (f + n) / (n - f),
			0, 0, 0, 1);
	}

	template<typename T>
	mat4x4<T>& mat4x4<T>::frustum(T l, T r, T b, T t, T n, T f)
	{
		return *this *= mat4x4(
			2 * n / (r - l), 0, (r + l) / (r - l), 0,
			0, 2 * n / (t - b), (t + b) / (t - b), 0,
			0, 0, (f + n) / (n - f), 2 * f * n / (n - f),
			0, 0, -1, 0);
	}

	template<typename T>
	mat4x4<T>& mat4x4<T>::perspective(T fov, T aspect, T near, T far)
	{
		T y = std::tan(fov * pi<T>() / 360) * near;
		T x = y * aspect;
		return frustum(-x, x, -y, y, near, far);
	}

	template<typename T>
	mat4x4<T>& mat4x4<T>::invert()
	{
		float t00 = m00, t01 = m01, t02 = m02, t03 = m03;
		*this = mat4x4<T>(
			m11*m22*m33 - m11*m32*m23 - m12*m21*m33 + m12*m31*m23 + m13*m21*m32 - m13*m31*m22,
			-m01*m22*m33 + m01*m32*m23 + m02*m21*m33 - m02*m31*m23 - m03*m21*m32 + m03*m31*m22,
			m01*m12*m33 - m01*m32*m13 - m02*m11*m33 + m02*m31*m13 + m03*m11*m32 - m03*m31*m12,
			-m01*m12*m23 + m01*m22*m13 + m02*m11*m23 - m02*m21*m13 - m03*m11*m22 + m03*m21*m12,

			-m10*m22*m33 + m10*m32*m23 + m12*m20*m33 - m12*m30*m23 - m13*m20*m32 + m13*m30*m22,
			m00*m22*m33 - m00*m32*m23 - m02*m20*m33 + m02*m30*m23 + m03*m20*m32 - m03*m30*m22,
			-m00*m12*m33 + m00*m32*m13 + m02*m10*m33 - m02*m30*m13 - m03*m10*m32 + m03*m30*m12,
			m00*m12*m23 - m00*m22*m13 - m02*m10*m23 + m02*m20*m13 + m03*m10*m22 - m03*m20*m12,

			m10*m21*m33 - m10*m31*m23 - m11*m20*m33 + m11*m30*m23 + m13*m20*m31 - m13*m30*m21,
			-m00*m21*m33 + m00*m31*m23 + m01*m20*m33 - m01*m30*m23 - m03*m20*m31 + m03*m30*m21,
			m00*m11*m33 - m00*m31*m13 - m01*m10*m33 + m01*m30*m13 + m03*m10*m31 - m03*m30*m11,
			-m00*m11*m23 + m00*m21*m13 + m01*m10*m23 - m01*m20*m13 - m03*m10*m21 + m03*m20*m11,

			-m10*m21*m32 + m10*m31*m22 + m11*m20*m32 - m11*m30*m22 - m12*m20*m31 + m12*m30*m21,
			m00*m21*m32 - m00*m31*m22 - m01*m20*m32 + m01*m30*m22 + m02*m20*m31 - m02*m30*m21,
			-m00*m11*m32 + m00*m31*m12 + m01*m10*m32 - m01*m30*m12 - m02*m10*m31 + m02*m30*m11,
			m00*m11*m22 - m00*m21*m12 - m01*m10*m22 + m01*m20*m12 + m02*m10*m21 - m02*m20*m11
			);

		float det = m00 * t00 + m10 * t01 + m20 * t02 + m30 * t03;
		for (int i = 0; i < 16; i++)
		{
			m[i] /= det;
		}

		return *this;
	}

	template<typename T>
	mat4x4<T>& mat4x4<T>::operator *= (const mat4x4<T>& t)
	{
		*this = mat4x4(
			m00*t.m00 + m01*t.m10 + m02*t.m20 + m03*t.m30,
			m00*t.m01 + m01*t.m11 + m02*t.m21 + m03*t.m31,
			m00*t.m02 + m01*t.m12 + m02*t.m22 + m03*t.m32,
			m00*t.m03 + m01*t.m13 + m02*t.m23 + m03*t.m33,

			m10*t.m00 + m11*t.m10 + m12*t.m20 + m13*t.m30,
			m10*t.m01 + m11*t.m11 + m12*t.m21 + m13*t.m31,
			m10*t.m02 + m11*t.m12 + m12*t.m22 + m13*t.m32,
			m10*t.m03 + m11*t.m13 + m12*t.m23 + m13*t.m33,

			m20*t.m00 + m21*t.m10 + m22*t.m20 + m23*t.m30,
			m20*t.m01 + m21*t.m11 + m22*t.m21 + m23*t.m31,
			m20*t.m02 + m21*t.m12 + m22*t.m22 + m23*t.m32,
			m20*t.m03 + m21*t.m13 + m22*t.m23 + m23*t.m33,

			m30*t.m00 + m31*t.m10 + m32*t.m20 + m33*t.m30,
			m30*t.m01 + m31*t.m11 + m32*t.m21 + m33*t.m31,
			m30*t.m02 + m31*t.m12 + m32*t.m22 + m33*t.m32,
			m30*t.m03 + m31*t.m13 + m32*t.m23 + m33*t.m33
			);
		return *this;
	}

	template<typename T>
	vec4<T> mat4x4<T>::operator*(const vec4<T>& v)
	{
		return vec4<T>(
			m00*v.x + m01*v.y + m02*v.z + m03*v.w,
			m10*v.x + m11*v.y + m12*v.z + m13*v.w,
			m20*v.x + m21*v.y + m22*v.z + m23*v.w,
			m30*v.x + m31*v.y + m32*v.z + m33*v.w
			);
	}

	template<typename T>
	vec4<T> operator*(const vec4<T>& v, const mat4x4<T>& t)
	{
		return vec4<T>(
			t.m00*v.x + t.m10*v.y + t.m20*v.z + t.m30*v.w,
			t.m01*v.x + t.m11*v.y + t.m21*v.z + t.m31*v.w,
			t.m02*v.x + t.m12*v.y + t.m22*v.z + t.m32*v.w,
			t.m03*v.x + t.m13*v.y + t.m23*v.z + t.m33*v.w
			);
	}
}