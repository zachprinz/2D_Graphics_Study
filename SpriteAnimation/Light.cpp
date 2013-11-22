#include "Light.h"

sf::Shader Light::lightShader;

Light::Light(int x,int y,sf::Color color,float radius,float intensity){
	position = sf::Vector2f(x,y);
	this->color = color;
	this->radius = radius;
	this->intensity = intensity;
	Calculate();
};
Light::Light(int x,int y,sf::Color color,float radius,float intensity,float spreadAngle,float spreadBeginAngle){
	position = sf::Vector2f(x,y);
	this->color = color;
	this->radius = radius;
	this->intensity = intensity;
	this->spreadAngle = spreadAngle;
	this->spreadBeginAngle = spreadBeginAngle;
	Calculate();
};
void Light::SetRadius(float newRadius){
	radius = newRadius;
	Calculate();
};
void Light::Calculate(){
	bounds = AABB(Vec2f(position.x - radius,position.y - radius),Vec2f(position.x + radius,position.y + radius));
	bounds.CalculateBounds();
	bounds.CalculateCenter();
	bounds.CalculateHalfDims();
};
sf::ConvexShape Light::GetShadowPolygon(ShadowLine*){
	sf::ConvexShape temp;
	return temp;
};
bool Light::CheckForIntersection(AABB bounds2){
	if(bounds.Intersects(bounds2))
		return true;
	else
		return false;
};
void Light::DrawDebug(sf::RenderTexture* panel){

};
AABB Light::GetBounds(){
	return bounds;
};