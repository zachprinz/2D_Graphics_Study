#include "Hull.h"

Hull::Hull(sf::ConvexShape poly){
	this->polygon = poly;
	Calculate();
};
void Hull::Calculate(){
	int minX = 0;
	int maxX = 0;
	int minY = 0;
	int maxY = 0;
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
	bounds.CalculateCenter();
	bounds.CalculateHalfDims();
};
void Hull::DrawDebug(sf::RenderTexture* panel){

};
AABB Hull::GetBounds(){
	return bounds;
};