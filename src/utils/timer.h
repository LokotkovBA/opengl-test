#pragma once

#include <Windows.h>


namespace GE {

	class Timer
	{
	private:
		LARGE_INTEGER m_Start;
		double m_Frequency;
		
	public:
		Timer()
		{
			LARGE_INTEGER freq;
			QueryPerformanceFrequency(&freq);
			m_Frequency = 1.0 / freq.QuadPart;
			QueryPerformanceCounter(&m_Start);
		}

		void reset()
		{
			QueryPerformanceCounter(&m_Start);
		}

		float elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned _int64 cycles = current.QuadPart - m_Start.QuadPart;
			return (float)(cycles * m_Frequency);
		}
	};
}