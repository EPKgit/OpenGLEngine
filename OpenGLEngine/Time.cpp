#include "Time.hpp"

float Time::GetCurrentTotalTime()
{
	return totalTime;
}

float Time::GetCurrentDeltaTime()
{
	return deltaTime;
}

float Time::Tick()
{
	deltaTime = clock.Restart();
	totalTime += deltaTime;
	return deltaTime;
}


float Clock::Restart()
{
	currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<double> temp = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - startTime);
	startTime = std::chrono::steady_clock::now();
	return (float)temp.count();
}
float Clock::GetTime()
{
	currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<double> temp = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - startTime);
	return temp.count();
}
Clock::Clock()
{
	startTime = currentTime = std::chrono::steady_clock::now();
}