#ifndef LIGHT_H
#define LIGHT_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include "AABB.h"
#include "ShadowLine.h"

class Light{ //Implements AABBREGION or QuadTree-able or something...
public:
	Light(int x,int y,sf::Color color,float radius,float intensity);
	Light(int x,int y,sf::Color color,float radius,float intensity,float spreadAngle,float spreadBeginAngle);
	static std::vector<int> lightTagList;
	void Calculate();
	sf::ConvexShape GetShadowPolygon(ShadowLine*);
	bool CheckForIntersection(AABB);
	void DrawDebug(sf::RenderTexture* panel);
	int tag;
	AABB GetBounds();
	void SetRadius(float);
private:
	static sf::Shader lightShader;
	float intensity;
	float radius;
	sf::Color color;
	sf::Vector2f position;
	AABB bounds;
	float spreadAngle;
	float spreadBeginAngle;
}

#endif