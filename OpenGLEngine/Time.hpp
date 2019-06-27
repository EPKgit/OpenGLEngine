#ifndef _TIME_HPP
#define _TIME_HPP

#include <chrono>

#include "Singleton.hpp"

class Clock
{
public:
	float Restart();
	float GetTime();
	Clock();
private:
	std::chrono::time_point<std::chrono::steady_clock> currentTime;
	std::chrono::time_point<std::chrono::steady_clock> startTime;
};

class Time : public Singleton<Time>
{
public:
	float GetCurrentTime();
	float GetCurrentDeltaTime();
	float Tick();
private:
	friend class Singleton<Time>;
	Time() : deltaTime(0), totalTime(0) { }
	float deltaTime;
	float totalTime;
	Clock clock;
};
#endif // !_TIME_HPP








