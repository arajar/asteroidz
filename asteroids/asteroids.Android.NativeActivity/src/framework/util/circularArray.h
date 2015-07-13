#pragma once

namespace util
{
	// super small circular array implementation
	template<typename T>
	class circularArray
	{
	public:
		circularArray(size_t capacity)
		{
			m_list.resize(capacity);
		}

		size_t getStart() { return m_start; }
		void   setStart(size_t value) { m_start = value; }
		size_t getCount() { return m_count; }
		void   setCount(size_t value) { m_count = value; }
		size_t size() { return m_list.size(); }

		T& operator[](const size_t i) { return m_list[(m_start + i) % m_list.size()]; }
		const T& operator[](const size_t i) const { return m_list[(m_start + i) % m_list.size()]; }

	protected:
		std::vector<T> m_list;
		size_t m_start;
		size_t m_count;
	};
}