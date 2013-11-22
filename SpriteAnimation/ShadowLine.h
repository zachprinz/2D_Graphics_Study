#ifndef SHADOWLINE_H
#define SHADOWLINE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "AABB.h"

class ShadowLine{
public:
	ShadowLine(sf::Vector2f,sf::Vector2f);
	ShadowLine();
	sf::Vector2f firstPoint;
	sf::Vector2f secondPoint;
	void Draw(sf::RenderTexture*,sf::Vector2f);
private:

};

#endif