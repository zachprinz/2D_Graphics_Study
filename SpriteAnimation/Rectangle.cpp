#include "Rectangle.h"

Rectangle::Rectangle(int x, int y, int width, int height){
	startPoint = sf::Vector2i(x,y);
	size = sf::Vector2i(width,height);
};
bool Rectangle::Intersects(Rectangle rect){
	if(!rect.CheckCorners(this) && !CheckCorners(&rect))
		return false;
	else
		return true;
};
Rectangle::Rectangle(){
	startPoint = sf::Vector2i(0,0);
	size = sf::Vector2i(0,0);
};
void Rectangle::SetRectangle(int x,int y,int width,int height){
	startPoint = sf::Vector2i(x,y);
	size = sf::Vector2i(width,height);
};
bool Rectangle::CheckCorners(Rectangle* rectB){
	if(Contains(rectB->startPoint.x, rectB->startPoint.y)
		|| Contains(rectB->startPoint.x, rectB->startPoint.y + rectB->size.y)
		|| Contains(rectB->startPoint.x + rectB->size.x, rectB->startPoint.y + rectB->size.y)
		|| Contains(rectB->startPoint.x + rectB->size.x, rectB->startPoint.y))
		return true;
	else
		return false;
};
bool Rectangle::Contains(int x,int y){
	if(x > startPoint.x && x < startPoint.x + size.x && y > startPoint.y && y < startPoint.y + size.y)
		return true;
	else 
		return false;
};
void Rectangle::SetPosition(int x,int y){
	startPoint.x = x;
	startPoint.y = y;
};
sf::Vector2i Rectangle::GetSize(){
	return size;
};
