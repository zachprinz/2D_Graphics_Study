#ifndef ROOM_H
#define ROOM_H

#include "RoomTile.h"
#include <vector>
#include <map>

class GameSprite;
class Room
{
public:
	Room();
	std::vector<std::vector<RoomTile>> roomTiles;
	void DrawTiles(sf::RenderTexture &window);
	void DrawOcupants(sf::RenderTexture &window);
	void AddOcupant(GameSprite*);
	void RemoveOcupant(int);
	RoomTile* GetRoomTile(int,int);
	GameSprite* GetOcupant(int tag);
	typedef std::map<int, GameSprite*> MyMap;
	typedef std::pair<int, GameSprite*> MyPair;
	std::vector<RoomTile*> grid;
	std::vector<int> openList;
	std::vector<int> closedList;
	std::vector<RoomTile*> GetPathTo(sf::Vector2i,sf::Vector2i); // switching x and y and what not.
	sf::Vector2i GetNextTileTo(sf::Vector2i,sf::Vector2i);
	int GetGridAddress(sf::Vector2i);
	sf::Vector2i GetArrayAddress(int);
private:
	std::vector<int> GetSurroundingTiles(int);
	void InsertToOpenList(int);
	int GetHValue(int,int);
	MyMap ocupantMap;
};

#endif