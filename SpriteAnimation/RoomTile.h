#ifndef ROOMTILE_H
#define ROOMTILE_H

#include <SFML/Graphics.hpp>
#include <vector>

class RoomTile
{
public:
	RoomTile(int x,int y);
	sf::Vector2i position;
	sf::RectangleShape getVisual();
	bool GetOcupied();
	void AddOcupant(int);
	void TryRemoveOcupant(int);
	std::vector<int> ocupants;
	void SetBlocked();
	void TileAttacked();
	int parent;
	int gValue;
	int hValue;
	int fValue;
	bool ContainsOcupant(int tag);
	std::vector<int> GetOcupantsBut(int tag);
	std::vector<int> GetOcupantsBut(std::vector<int>);
private:
	bool ocupied;
	sf::RectangleShape visual;
};

#endif