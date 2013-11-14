#ifndef ARECTANGLE_H
#define ARECTANGLE_H

#include <vector>
#include <SFML/Graphics.hpp>

class ARectangle
{
public:
	ARectangle(int x, int y, int width, int height);
	ARectangle();
	void SetRectangle(int,int,int,int);
	bool Intersects(ARectangle);
	bool Contains(int,int);
	void SetPosition(int,int);
	sf::Vector2i GetSize();
private:
	bool CheckCorners(ARectangle*);
	sf::Vector2i startPoint;
	sf::Vector2i size;
};

#endif