#include "Hull.h"

Hull::Hull(sf::ConvexShape poly,sf::Vector2f pos,float height){
	this->height = height;
	poly.setPosition(pos);
	this->polygon = poly;
	Calculate();
};
Hull::Hull(ShadowLine sl,sf::Vector2f pos,float height){
	this->height = height;
	sl.firstPoint = sf::Vector2f(sl.firstPoint.x + pos.x,sl.firstPoint.y + pos.y);
	sl.secondPoint = sf::Vector2f(sl.secondPoint.x + pos.x, sl.secondPoint.y + pos.y);
	shadowLines.push_back(sl);
	polygon.setPointCount(4);
	polygon.setPoint(0,(sf::Vector2f(sl.firstPoint.x,sl.firstPoint.y)));
	polygon.setPoint(1,(sf::Vector2f(sl.secondPoint.x,sl.firstPoint.y)));
	polygon.setPoint(2,(sf::Vector2f(sl.firstPoint.x,sl.secondPoint.y)));
	polygon.setPoint(3,(sf::Vector2f(sl.secondPoint.x,sl.secondPoint.y)));
	Calculate();
};
Hull::Hull(){

};
void Hull::SetLines(std::vector<ShadowLine> sls){
	shadowLines.clear();
	for(int x = 0; x < sls.size(); x++){
		shadowLines.push_back(sls[x]);
	};
};
void Hull::SetLines(ShadowLine sl,sf::Vector2f pos){
	shadowLines.clear();
	sl.firstPoint = sf::Vector2f(sl.firstPoint.x + pos.x,sl.firstPoint.y + pos.y);
	sl.secondPoint = sf::Vector2f(sl.secondPoint.x + pos.x, sl.secondPoint.y + pos.y);
	shadowLines.push_back(sl);
	sf::ConvexShape temp;
	polygon = temp;
	polygon.setPointCount(4);
	polygon.setPoint(0,(sf::Vector2f(sl.firstPoint.x,sl.firstPoint.y)));
	polygon.setPoint(1,(sf::Vector2f(sl.secondPoint.x,sl.firstPoint.y)));
	polygon.setPoint(2,(sf::Vector2f(sl.firstPoint.x,sl.secondPoint.y)));
	polygon.setPoint(3,(sf::Vector2f(sl.secondPoint.x,sl.secondPoint.y)));
	Calculate();
};
void Hull::Calculate(){
	int minX = polygon.getPoint(0).x;
	int maxX = polygon.getPoint(0).x;
	int minY = polygon.getPoint(0).y;
	int maxY = polygon.getPoint(0).y;
	for(int z = 0; z < polygon.getPointCount(); z++){
		int x = polygon.getPoint(z).x;
		int y = polygon.getPoint(z).y;
		if(x > maxX)
			maxX = x;
		if(x < minX)
				minX = x;
		if(y > maxY)
			maxY = y;
		if(y < minY)
				minY = y;
	}
	bounds = AABB(Vec2f(minX,minY),Vec2f(maxX,maxY));
	bounds.CalculateBounds();
	bounds.CalculateCenter();
	bounds.CalculateHalfDims();
};
void Hull::DrawDebug(sf::RenderTexture* panel){

};
AABB Hull::GetBounds(){
	return bounds;
};
Vec2f Hull::GetPoint(){
	return bounds.GetLowerBound();
};
void Hull::SetPosition(sf::Vector2f newpos){
	position = newpos;
};