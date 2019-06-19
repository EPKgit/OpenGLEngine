#include "Time.hpp"

float Time::GetCurrentTime()
{
	return totalTime;
}

float Time::GetCurrentDeltaTime()
{
	return deltaTime;
}

void Time::Tick()
{
	deltaTime = clock.Restart();
	totalTime += deltaTime;
}


float Clock::Restart()
{
	currentTime = std::chrono::steady_clock::now();
	float temp = (currentTime - startTime).count();
	startTime = std::chrono::steady_clock::now();
	return temp;
}
float Clock::GetTime()
{
	currentTime = std::chrono::steady_clock::now();
	return (currentTime - startTime).count();
}
Clock::Clock()
{
	startTime = currentTime = std::chrono::steady_clock::now();
}