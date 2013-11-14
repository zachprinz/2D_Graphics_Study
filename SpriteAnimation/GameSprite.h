#ifndef GAMESPRITE_H
#define GAMESPRITE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "RClickable.h"
#include "ARectangle.h"
#include "Room.h"
#include "LTBL\Light\ConvexHull.h"

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
	static bool displayDebug;
	virtual void Update(sf::RenderTexture&);
	void AddBoundryPolygon(sf::ConvexShape);
	void ClearBoundries();
	void DrawBoundries(sf::RenderTexture&);
protected:
	std::vector<sf::ConvexShape> boundries;
	std::vector<ltbl::ConvexHull*> hulls;
	RoomTile* GetRoomTile();
	RoomTile* GetRoomTile(int,int);
	void UpdateRoomTile();
	sf::Vector2f posB;
	bool isVisible;
	static int tagCount;
	int tag;
	int z;
	ARectangle groundSpace;
	sf::Vector2i graphPositionA;
};

#endif