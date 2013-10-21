#include "Animation.h"

Animation::Animation(std::string name, float perFrame,int numFramesA,int width,int up,int down,int left,int right){
	this->name = name;
	timePerFrame = sf::seconds(perFrame);
	numFrames = numFramesA;
	yValues.push_back(up);
	yValues.push_back(down);
	yValues.push_back(left);
	yValues.push_back(right);
	this->width = width;
};
int Animation::GetY(AnimDir dir){
	return yValues[dir];
};

