
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
	vec3_type<T> cross(const vec3_type<T>& a, const vec3_type<T>& b)
	{
		return vec3_type<T>(x.y * y.z - y.y * x.z,
							x.z * y.x - y.z * x.x,
							x.x * y.y - y.x * x.y);
	}

	template<typename T>
	vec2_type<T> normalize(const vec2_type<T>& v)
	{
		return v * (static_cast<T>(1) / sqrt(length(v)));
	}

	template<typename T>
	vec3_type<T> normalize(const vec3_type<T>& v)
	{
		return v * (static_cast<T>(1) / sqrt(length(v)));
	}

	template<typename T>
	vec4_type<T> normalize(const vec4_type<T>& v)
	{
		return v * (static_cast<T>(1) / sqrt(length(v)));
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
	mat4_type<T> ortho(T left, T right, T bottom, T top)
	{
		mat4_type<T> res(static_cast<T>(1));
		res[0][0] = static_cast<T>(2) / (right - left);
		res[1][1] = static_cast<T>(2) / (top - bottom);
		res[2][2] = -static_cast<T>(1);
		res[3][0] = -(right + left) / (right - left);
		res[3][1] = -(top + bottom) / (top - bottom);
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
	const T* toGl(const vec2_type<T>& v) { return &(v.x); }

	template<typename T>
	const T* toGl(const vec3_type<T>& v) { return &(v.x); }

	template<typename T>
	const T* toGl(const vec4_type<T>& v) { return &(v.x); }

	template<typename T>
	const T* toGl(const mat4_type<T>& m) { return &(m[0].x); }
}
