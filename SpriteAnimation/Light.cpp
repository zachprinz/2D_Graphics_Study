#include "Light.h"
#include "Hull.h"
#include "User.h"

sf::Shader Light::lightShader;
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
		SetRadius(130 + 4*((float)std::sin(zAngle)) + 0.5f* (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/10.0f)))-5.0f);
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
sf::ConvexShape Light::GetShadowPolygon(ShadowLine* sl,Hull* hull,sf::Vector2f offset){
	//oscilate
	sf::ConvexShape temp;
	temp.setPointCount(4);
	ShadowLine firstLine = GetPointShadowLine(sl->firstPoint,hull,offset);
	ShadowLine secondLine = GetPointShadowLine(sl->secondPoint,hull,offset);
	if(hull == User::player->actorHull){ ///TODO: I feel horrible for using this solution...
		if(sl->firstPoint.y > bounds.GetCenter().y && sl->secondPoint.y > bounds.GetCenter().y){
			temp.setPoint(0,firstLine.firstPoint);
			temp.setPoint(1,firstLine.secondPoint);
			temp.setPoint(3,secondLine.firstPoint);
			temp.setPoint(2,secondLine.secondPoint);
		}
		else {
			temp.setPoint(0,firstLine.secondPoint);
			temp.setPoint(3,firstLine.firstPoint);
			temp.setPoint(1,secondLine.secondPoint);
			temp.setPoint(2,secondLine.firstPoint);
			temp.setOrigin(temp.getPoint(1) - temp.getPoint(2));
		}
	}
	else{
		if(sl->firstPoint.y < bounds.GetCenter().y && sl->secondPoint.y < bounds.GetCenter().y){
			temp.setPoint(0,firstLine.firstPoint);
			temp.setPoint(1,firstLine.secondPoint);
			temp.setPoint(3,secondLine.firstPoint);
			temp.setPoint(2,secondLine.secondPoint);
		}
		else {
			temp.setPoint(0,firstLine.secondPoint);
			temp.setPoint(3,firstLine.firstPoint);
			temp.setPoint(1,secondLine.secondPoint);
			temp.setPoint(2,secondLine.firstPoint);
			temp.setOrigin(temp.getPoint(1) - temp.getPoint(2));
		}
	}
	return temp;
};
ShadowLine Light::GetPointShadowLine(sf::Vector2f point,Hull* hull,sf::Vector2f offset){
	Vec2f centerPoint = bounds.GetCenter();
	centerPoint.x += offset.x;
	centerPoint.y += offset.y;
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
	ShadowLine returnShadowLine(point,point2);
	return returnShadowLine;
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