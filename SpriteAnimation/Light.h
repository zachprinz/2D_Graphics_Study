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
	void GetShadowQuad(ShadowLine*,Hull*,sf::Vector2f,sf::Vertex*);
	bool CheckForIntersection(AABB);
	void DrawDebug(sf::RenderTexture* panel);
	int tag;
	AABB GetBounds();
	void SetRadius(float);
	float height;
	sf::Vector2f position;
	float radius;
	sf::Color color;
	void Update();
	float zAngle;
	bool oscillate;
	sf::Clock oscillateClock;
	static double PI2;
	static float zSpeed;
private:
	bool oscillateFrame;
	ShadowLine GetPointShadowLine(sf::Vector2f,Hull*,sf::Vector2f);
	static sf::Shader lightShader;
	float intensity;
	AABB bounds;
	float spreadAngle;
	float spreadBeginAngle;
};
#endif