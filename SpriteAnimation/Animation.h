#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <cmath>

class Animation
{
public:
	enum AnimDir {Up,Down,Left,Right};
	Animation(std::string name, float perFrame,int numFramesA,int width,int up,int down,int left,int right,int id);
	int GetY(AnimDir);
	int numFrames;
	std::vector<int> yValues;
	sf::Time timePerFrame;
	std::string name;
	int width;
	int id;
private:

};

#endif