#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <vector>
#include <SFML/Graphics.hpp>

class Rectangle
{
public:
	Rectangle(int x, int y, int width, int height);
	Rectangle();
	void SetRectangle(int,int,int,int);
	bool Intersects(Rectangle);
	bool Contains(int,int);
	void SetPosition(int,int);
	sf::Vector2i GetSize();
private:
	bool CheckCorners(Rectangle*);
	sf::Vector2i startPoint;
	sf::Vector2i size;
};

#endif