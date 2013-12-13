#ifndef CLOCK_H
#define CLOCK_H

#include "SFML\Graphics.hpp"

class Clock
{
public:
	Clock();
	void Update(sf::Time);
	static void UpdateAll();
	sf::Time getElapsedTime();
	sf::Time restart();
	static float timeSpeed;
	static sf::Clock myClock;
	static void SlowTime(float,float);
	static void ReturnTime();
	static void UpdateSlowTime();
private:
	static std::vector<Clock*> clocks;
	sf::Time elapsedTime;
	sf::Time frameTime;
	static float targetSlowTime;
	static float slowTimeDirection;
	static float slowTimePerSecond;
	static sf::Clock slowTimeClock;
	static bool isSlowing;
};
#endif