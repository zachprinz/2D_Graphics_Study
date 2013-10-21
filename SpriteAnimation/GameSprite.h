#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "RClickable.h"
#include "Rectangle.h"
#include "Room.h"

class Room;
class GameSprite : public RClickable
{
public:
	GameSprite(int,int,std::string);
	GameSprite();
	void AdjustZToUser();
	int GetZ();
	void SetZ(int);
	int GetTag();
	virtual void Interact();
	virtual void RecieveAttack(int);
	sf::Vector2i GetGraphPositionA();
	void SetGraphPositionA(sf::Vector2i);
	void SetLocation(float,float);
	virtual void OnClick();
	virtual void OnHover();
protected:
	RoomTile* GetRoomTile();
	RoomTile* GetRoomTile(int,int);
	void UpdateRoomTile();
	sf::Vector2f posB;
	bool isVisible;
	static int tagCount;
	int tag;
	int z;
	Rectangle groundSpace;
	sf::Vector2i graphPositionA;
};

#endif