#ifndef GROUNDITEMSPAWNER_H
#define GROUNDITEMSPAWNER_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "RClickable.h"
#include "GroundItem.h"
#include "Room.h"

class GroundItemSpawner
{
public:
	typedef std::pair<std::string, Drawn*> MyPair;
	static MyPair CreateItem(int id,int x,int y,Room*);
};

#endif