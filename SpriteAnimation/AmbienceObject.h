#ifndef AMBIENCEOBJECT_H
#define AMBIENCEOBJECT_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "GameSprite.h"
#include <string>
#include <MapLoader.h>


class AmbienceObject :  public GameSprite
{

public:
	AmbienceObject(int,int,std::string,std::string);
	AmbienceObject(int,int,tmx::MapObject*);
	void Update(sf::RenderTexture&);
	void Update2(sf::RenderTexture&);
	void Interact();
	void OnClick();
	void SetNonphysical(std::string);
	void SetNonphysical(GameSprite*);
	GameSprite* GetNonphysical();
	sf::Vector2i GetPhysicalPosition(int x, int y, tmx::MapObject*);
	static std::vector<std::string> tags;
private:
	void SetUpBoundries(std::string,GameSprite* target);
	GameSprite* nonphysical;
};

#endif