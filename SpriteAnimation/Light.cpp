#include "Light.h"
#include "Hull.h"
#include "User.h"

float Light::zSpeed = 1.0f;
double Light::PI2 = 3.1415926535897932384626433832795f * 2.0f;

Light::Light(int x,int y,sf::Color color,float radius,float intensity,float height){
	oscillate = true;
	if(oscillate){
		int v1 = rand() % 100;
		if(v1 > 50)
			oscillateFrame = true;
		else
			oscillateFrame = false;
	}
	this->height = height;
	position = sf::Vector2f(x,y);
	this->color = color;
	this->radius = radius;
	this->intensity = intensity;
	Calculate();
};
Light::Light(int x,int y,sf::Color color,float radius,float intensity,float height,float spreadAngle,float spreadBeginAngle){
	oscillate = true;
	if(oscillate){
		int v1 = rand() % 100;
		if(v1 > 50)
			oscillateFrame = true;
		else
			oscillateFrame = false;
	}
	this->height = height;
	position = sf::Vector2f(x,y);
	this->color = color;
	this->radius = radius;
	this->intensity = intensity;
	this->spreadAngle = spreadAngle;
	this->spreadBeginAngle = spreadBeginAngle;
	Calculate();
};
void Light::Update(){
	if(oscillateFrame){
	zAngle += (oscillateClock.restart().asMilliseconds()) * zSpeed;
	while(zAngle > PI2)
		zAngle -= PI2;
	if(oscillate)
		SetRadius(130 + 3*((float)std::sin(zAngle)));// + 0.5f* (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/10.0f)))-5.0f);
	oscillateFrame = false;
	}
	else
		oscillateFrame = true;
};
void Light::SetRadius(float newRadius){
	radius = newRadius;
	Calculate();
};
void Light::Calculate(){
	bounds = AABB(Vec2f(position.x - radius,position.y - radius),Vec2f(position.x + radius,position.y + radius));
	bounds.CalculateCenter();
	bounds.CalculateHalfDims();
	bounds.CalculateBounds();

};
void Light::GetShadowQuad(ShadowLine* sl,Hull* hull,sf::Vector2f offset,sf::Vertex* temp){
	sf::Vector2f off(-11.2,-9.6);
	sf::Vector2f off2(-11.2,-9.6);
	ShadowLine firstLine = GetPointShadowLine(sl->firstPoint,hull,offset);
	ShadowLine secondLine = GetPointShadowLine(sl->secondPoint,hull,offset);
	if(hull == User::player->GetHull()){
		if(sl->firstPoint.y > bounds.GetCenter().y && sl->secondPoint.y > bounds.GetCenter().y){
			temp[0].position= firstLine.firstPoint + off;
			temp[3].position= firstLine.secondPoint + off;
			temp[1].position= secondLine.firstPoint + off;
			temp[2].position= secondLine.secondPoint + off;
		}
		else {
			temp[0].position= firstLine.secondPoint - firstLine.size + off2;
			temp[2].position= secondLine.firstPoint - secondLine.size + off2;
			temp[1].position= secondLine.secondPoint - secondLine.size + off2;
			temp[3].position= firstLine.firstPoint - firstLine.size + off2;
		}
	}
	else{
		if(sl->firstPoint.y < bounds.GetCenter().y && sl->secondPoint.y < bounds.GetCenter().y){
			temp[0].position= firstLine.firstPoint + off;
			temp[3].position= firstLine.secondPoint + off;
			temp[1].position= secondLine.firstPoint + off;
			temp[2].position= secondLine.secondPoint + off;
		}
		else {
			temp[0].position= firstLine.secondPoint - firstLine.size + off2;
			temp[2].position= secondLine.firstPoint - secondLine.size + off2;
			temp[1].position= secondLine.secondPoint - secondLine.size + off2;
			temp[3].position= firstLine.firstPoint - firstLine.size + off2;
		}
	}
	temp[0].color = sf::Color(0,0,0,255);
	temp[1].color = sf::Color(0,0,0,255);
	temp[2].color = sf::Color(0,0,0,255);
	temp[3].color = sf::Color(0,0,0,255);
};
ShadowLine Light::GetPointShadowLine(sf::Vector2f point,Hull* hull,sf::Vector2f offset){
	Vec2f centerPoint = bounds.GetCenter();
	centerPoint.x += offset.x - position.x + radius;
	centerPoint.y += offset.y - position.y + radius;
	point.x -= position.x - radius;
	point.y -= position.y - radius;
	float distance = std::sqrt(std::pow((centerPoint.x - point.x),2) + std::pow((centerPoint.y - point.y),2));
	float slope;
	if(point.x != centerPoint.x)
		slope = ((float)(centerPoint.y - point.y))/((float)(centerPoint.x - point.x));
	else{
		if(centerPoint.y > point.y)
			slope = -99999999;
		else
			slope =  99999999;
	}
	float length = hull->height * ((distance)/((float)(height - hull->height)));
	float theta = std::atan((centerPoint.x - point.x)/(centerPoint.y - point.y));
	float shadowXDistance = length*sin(theta);
	float shadowYDistance = length*cos(theta);
	sf::Vector2f point2;
	point2.x += point.x + shadowXDistance;
	point2.y += point.y + shadowYDistance;
	ShadowLine ret;
	ret.firstPoint = point;
	ret.secondPoint = point2;
	ret.size.x = shadowXDistance;
	ret.size.y = shadowYDistance;
	return ret;
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
Vec2f Light::GetPoint(){
	return bounds.GetLowerBound();
};