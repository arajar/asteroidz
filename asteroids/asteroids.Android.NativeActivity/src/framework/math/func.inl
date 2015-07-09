
namespace math
{
	template<typename T>
	inline T pi()
	{
		return static_cast<T>(3.14159265358979323846264338327950288);
	}

	template<typename T>
	inline T toDeg(T angle)
	{
		return (angle * (static_cast<T>(180)) / pi<T>());
	}

	template<typename T>
	inline T toRad(T angle)
	{
		return angle * (pi<T>() / static_cast<T>(180));
	}

	template<typename T>
	float length(const vec2_type<T>& v) { return std::sqrt(dot(v, v)); }

	template<typename T>
	float length(const vec3_type<T>& v) { return std::sqrt(dot(v, v)); }

	template<typename T>
	float length(const vec4_type<T>& v) { return std::sqrt(dot(v, v)); }

	template<typename T>
	float dot(const vec2_type<T>& a, const vec2_type<T>& b)
	{
		vec2_type<T> tmp(a * b);
		return tmp.x + tmp.y;
	}

	template<typename T>
	float dot(const vec3_type<T>& a, const vec3_type<T>& b)
	{
		vec3_type<T> tmp(a * b);
		return tmp.x + tmp.y + tmp.z;
	}
	
	template<typename T>
	float dot(const vec4_type<T>& a, const vec4_type<T>& b)
	{
		vec4_type<T> tmp(a * b);
		return tmp.x + tmp.y + tmp.z + tmp.w;
	}

	template<typename T>
	T clamp(T val, T minVal, T maxVal)
	{
		T max = val > minVal ? val : minVal;
		return max < maxVal ? max : maxVal;
	}

	template<typename T>
	vec3_type<T> cross(const vec3_type<T>& x, const vec3_type<T>& y)
	{
		return vec3_type<T>(x.y * y.z - y.y * x.z,
							x.z * y.x - y.z * x.x,
							x.x * y.y - y.x * x.y);
	}

	template<typename T>
	vec2_type<T> normalize(const vec2_type<T>& v)
	{
		return v * (static_cast<T>(1) / std::sqrt(length(v)));
	}

	template<typename T>
	vec3_type<T> normalize(const vec3_type<T>& v)
	{
		return v * (static_cast<T>(1) / std::sqrt(length(v)));
	}

	template<typename T>
	vec4_type<T> normalize(const vec4_type<T>& v)
	{
		return v * (static_cast<T>(1) / std::sqrt(length(v)));
	}

	template<typename T>
	mat4_type<T> perspective(T fov, T aspect, T near, T far)
	{
		const T tanHalfFov = std::tan(fov / static_cast<T>(2));
		mat4_type<T> res(static_cast<T>(0));
		res[0][0] = static_cast<T>(1) / (aspect * tanHalfFov);
		res[1][1] = static_cast<T>(1) / (tanHalfFov);
		res[2][2] = -(far + near) / (far - near);
		res[2][3] = -static_cast<T>(1);
		res[3][2] = -(static_cast<T>(2) * far * near) / (far - near);
		return res;
	}

	template<typename T>
	mat4_type<T> ortho(T left, T right, T bottom, T top, T near, T far)
	{
		mat4_type<T> res(static_cast<T>(1));
		res[0][0] = static_cast<T>(2) / (right - left);
		res[1][1] = static_cast<T>(2) / (top - bottom);
		res[2][2] = -static_cast<T>(2) / (far - near);
		res[3][0] = -(right + left) / (right - left);
		res[3][1] = -(top + bottom) / (top - bottom);
		res[3][2] = -(far + near) / (far - near);
		return res;
	}

	template<typename T>
	mat4_type<T> lookAt(const vec3_type<T>& eye, const vec3_type<T>& center, const vec3_type<T>& up)
	{
		const vec3_type<T> f(normalize(center - eye));
		const vec3_type<T> s(normalize(cross(f, up)));
		const vec3_type<T> u(cross(s, f));

		mat4_type<T> res(static_cast<T>(1));
		res[0][0] = s.x;
		res[1][0] = s.y;
		res[2][0] = s.z;
		res[0][1] = u.x;
		res[1][1] = u.y;
		res[2][1] = u.z;
		res[0][2] = -f.x;
		res[1][2] = -f.y;
		res[2][2] = -f.z;
		res[3][0] = -dot(s, eye);
		res[3][1] = -dot(u, eye);
		res[3][2] = dot(f, eye);
		return res;
	}

	template<typename T>
	mat4_type<T> inverse(const mat4_type<T>& m)
	{
		T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		vec4_type<T> Fac0(Coef00, Coef00, Coef02, Coef03);
		vec4_type<T> Fac1(Coef04, Coef04, Coef06, Coef07);
		vec4_type<T> Fac2(Coef08, Coef08, Coef10, Coef11);
		vec4_type<T> Fac3(Coef12, Coef12, Coef14, Coef15);
		vec4_type<T> Fac4(Coef16, Coef16, Coef18, Coef19);
		vec4_type<T> Fac5(Coef20, Coef20, Coef22, Coef23);

		vec4_type<T> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
		vec4_type<T> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		vec4_type<T> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		vec4_type<T> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

		vec4_type<T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		vec4_type<T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		vec4_type<T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		vec4_type<T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

		vec4_type<T> SignA(+1, -1, +1, -1);
		vec4_type<T> SignB(-1, +1, -1, +1);
		mat4_type<T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

		vec4_type<T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

		vec4_type<T> Dot0(m[0] * Row0);
		T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

		T OneOverDeterminant = static_cast<T>(1) / Dot1;

		return Inverse * OneOverDeterminant;
	}

	template<typename T>
	mat4_type<T> translate(const mat4_type<T>& m, const vec3_type<T>& v)
	{
		mat4_type<T> res = m;
		res[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
		return res;
	}

	template<typename T>
	mat4_type<T> rotate(const mat4_type<T>& m, T angle, const vec3_type<T>& v)
	{
		const T a = angle;
		const T c = std::cos(a);
		const T s = std::sin(a);

		auto axis(normalize(v));
		auto temp = axis * (T(1) - c);

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
	mat4_type<T> scale(const mat4_type<T>& m, const vec3_type<T>& v)
	{
		mat4_type<T> res;
		res[0] = m[0] * v[0];
		res[1] = m[1] * v[1];
		res[2] = m[2] * v[2];
		res[3] = m[3];
		return res;
	}

	template<typename T>
	const T* toGl(const vec2_type<T>& v) { return &(v.x); }

	template<typename T>
	const T* toGl(const vec3_type<T>& v) { return &(v.x); }

	template<typename T>
	const T* toGl(const vec4_type<T>& v) { return &(v.x); }

	template<typename T>
	const T* toGl(const mat4_type<T>& m) { return &(m[0].x); }
}
