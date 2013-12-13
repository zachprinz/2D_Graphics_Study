#include "Clock.h"
#include "Actor.h"
#include <iostream>

float Clock::timeSpeed;
sf::Clock Clock::myClock;
std::vector<Clock*> Clock::clocks;
float Clock::targetSlowTime;
float Clock::slowTimeDirection;
float Clock::slowTimePerSecond;
sf::Clock Clock::slowTimeClock;
bool Clock::isSlowing;

Clock::Clock(){
	clocks.push_back(this);
	elapsedTime = sf::seconds(0);
};
void Clock::Update(sf::Time time){
	elapsedTime += time;
	frameTime = elapsedTime;
};
void Clock::UpdateAll(){
	UpdateSlowTime();
	sf::Time temp = myClock.restart() * timeSpeed;
	for(int x = 0; x < clocks.size(); x++){
		clocks[x]->Update(temp);
	}
};
sf::Time Clock::restart(){
	elapsedTime = sf::seconds(0);
	return frameTime;
};
sf::Time Clock::getElapsedTime(){
		return frameTime;
};
void Clock::SlowTime(float time,float factor){
	slowTimePerSecond = abs(timeSpeed - factor) / time;
	slowTimeDirection = -1;
	targetSlowTime = factor;
	slowTimeClock.restart();
	isSlowing = true;
};
void Clock::ReturnTime(){
	slowTimePerSecond = abs(1 - timeSpeed) / 0.5;
	slowTimeDirection = 1;
	targetSlowTime = 1;
	slowTimeClock.restart();
	isSlowing = true;
};
void Clock::UpdateSlowTime(){
	if(isSlowing){
		float slowTimeAmount = slowTimePerSecond * slowTimeClock.restart().asSeconds() * slowTimeDirection;
		if(slowTimeDirection > 0){
			if(timeSpeed + slowTimeAmount < targetSlowTime)
				timeSpeed += slowTimeAmount;
			else{
				timeSpeed = targetSlowTime;
				isSlowing = false;
			}
		}
		else{
			if(timeSpeed + slowTimeAmount > targetSlowTime)
				timeSpeed = timeSpeed + slowTimeAmount;
			else{
				timeSpeed = targetSlowTime;
				isSlowing = false;
			}
		}
	}
};