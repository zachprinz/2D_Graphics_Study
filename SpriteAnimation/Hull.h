#ifndef HULL_H
#define HULL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "AABB.h"

class Hull{ //Implements AABBREGION or QuadTree-able or something...
public:
	void CalculateAABB();
	static std::vector<int> hullTagList;
	int tag;
	void DrawDebug(sf::RenderTexture* panel);
private:
	sf::ConvexShape polygon;
	sf::Vector2f position;
	AABB bounds;
};
#endif