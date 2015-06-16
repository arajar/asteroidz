
namespace m
{
	template<typename T>
	inline T pi()
	{
		return static_cast<T>(3.14159265358979323846264338327950288);
	}
	
	template<typename T>
	inline T toDeg(T angle)
	{
		return (angle * (static_cast<T>(180)) / pi<T>);
	}
	
	template<typename T>
	inline T toRad(T angle)
	{
		return angle * (pi<T> / static_cast<T>(180));
	}
}
