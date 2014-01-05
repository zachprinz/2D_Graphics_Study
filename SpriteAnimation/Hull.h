#ifndef HULL_H
#define HULL_H

#include <SFML/Graphics.hpp>
#include "AABB.h"
#include "ShadowLine.h"
#include "GameSprite.h"

class Hull{
public:
	Hull(sf::ConvexShape poly,sf::Vector2f,float height,GameSprite*);
	Hull(ShadowLine sl,sf::Vector2f,float height,GameSprite*);
	Hull();
	Vec2f GetPoint();
	void SetLines(std::vector<ShadowLine>);
	void SetLines(ShadowLine,sf::Vector2f);
	void Calculate();
	static std::vector<int> hullTagList;
	int tag;
	float height;
	void DrawDebug(sf::RenderTexture* panel);
	AABB GetBounds();
	std::vector<ShadowLine> shadowLines;
	void SetPosition(sf::Vector2f);
	GameSprite* mySprite;
private:
	sf::ConvexShape polygon;
	sf::Vector2f position;
	AABB bounds;
};

#endif