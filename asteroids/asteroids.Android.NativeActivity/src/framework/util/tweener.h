#pragma once

typedef std::function<float(float)> InterpolationFunction;

namespace util
{
	// A c++11 tweener class
	// interpolates values over time with a custom interpolation function
	template<typename InterpType>
	class tweener
	{
	public:
		tweener()
			: m_interpFunction(nullptr)
			, m_initialValue()
			, m_currentValue()
			, m_targetValue()
			, m_delayTime(0)
			, m_accumTime(0)
			, m_updating(true)
		{
		}

		tweener(InterpolationFunction interpFunction, InterpType initialValue, InterpType targetValue, uint delay)
			: m_interpFunction(interpFunction)
			, m_initialValue(initialValue)
			, m_currentValue(initialValue)
			, m_targetValue(targetValue)
			, m_delayTime(delay)
			, m_accumTime(0)
			, m_updating(m_initialValue != m_targetValue)
		{
		}

		virtual ~tweener() {}

	public:
		bool update(float deltaTime)
		{
			if (m_interpFunction)
			{
				if (m_updating)
				{
					m_accumTime += deltaTime;
					if (m_accumTime >= m_delayTime)
					{
						m_currentValue = m_targetValue;
						m_updating = false;
					}
					else
					{
						float t = static_cast<float>(m_accumTime) / static_cast<float>(m_delayTime);
						t = m_interpFunction(t);

						m_currentValue = m_initialValue + (m_targetValue - m_initialValue) * t;
					}
					return true;
				}
				return false;
			}
			return false;
		}


	public:
		InterpType getValue() const
		{
			return m_currentValue;
		}

		uint getDelay() const
		{
			return m_delayTime;
		}

		InterpType getInitialValue() const
		{
			return m_initialValue;
		}

		InterpType getTargetValue() const
		{
			return m_targetValue;
		}

		bool hasFinished() const
		{
			return !m_updating;
		}

	public:
		void setEaseFunction(InterpolationFunction func)
		{
			m_interpFunction = func;
		}

		void reset(InterpType initial, InterpType target)
		{
			m_initialValue = initial;
			m_currentValue = initial;
			m_targetValue = target;
			m_accumTime = 0;
			m_updating = true;
		}

		void setDelay(uint delay)
		{
			m_delayTime = delay;
			m_accumTime = 0;
		}

		void setTargetValue(InterpType value)
		{
			m_targetValue = value;
			m_initialValue = m_currentValue;
			m_updating = m_targetValue != m_currentValue;
		}

	private:
		InterpolationFunction m_interpFunction;

	private:
		InterpType m_initialValue;
		InterpType m_currentValue;
		InterpType m_targetValue;
		uint m_delayTime;
		float m_accumTime;
		bool m_updating;
	};
}
