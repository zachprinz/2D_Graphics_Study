#ifndef LIGHT_H
#define LIGHT_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "ShadowLine.h"
#include "Hull.h"

class Light
{
public:
	Light(int x,int y,sf::Color color,float radius,float intensity,float height);
	Light(int x,int y,sf::Color color,float radius,float intensity,float height,float spreadAngle,float spreadBeginAngle);
	static std::vector<int> lightTagList;
	void Calculate();
	Vec2f GetPoint();
	sf::ConvexShape GetShadowPolygon(ShadowLine*,Hull*,sf::Vector2f);
	bool CheckForIntersection(AABB);
	void DrawDebug(sf::RenderTexture* panel);
	int tag;
	AABB GetBounds();
	void SetRadius(float);
	float height;
	sf::Vector2f position;
	float radius;
	sf::Color color;
private:
	ShadowLine GetPointShadowLine(sf::Vector2f,Hull*,sf::Vector2f);
	static sf::Shader lightShader;
	float intensity;
	AABB bounds;
	float spreadAngle;
	float spreadBeginAngle;
};
#endif