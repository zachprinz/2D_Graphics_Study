#ifndef SLICEDSPRITE_H
#define SLICEDSPRITE_H

#include "Drawn.h"

class SlicedSprite : public Drawn
{
public:
	static sf::Sprite* backgroundLeft;
	static sf::Sprite* backgroundRight;
	static sf::Sprite* backgroundCenter;
	static sf::Sprite* foregroundCenter;
	static std::vector<std::vector<sf::IntRect>> spriteParts;
	static std::vector<std::vector<sf::IntRect>> scrollBarParts;
	static enum Parts {TopLeft,Top,TopRight,Left,Center,Right,BottomLeft,Bottom,BottomRight};
	static enum SpriteStyle {Pixel,WoodPanel,TextPanel,Last};
	static void OnStart();
	SlicedSprite(int,int,float,float,SlicedSprite::SpriteStyle);
	SlicedSprite(int,int,int);
	void CreateTiled(int,int,int,std::string);
	void SetPosition(sf::Vector2f);
	void SetZ(int z);
	void Update(GamePanel*);
	sf::Vector2f GetSize();
	void SetRotation(float angle);
	void SetSlicedOrigin(sf::Vector2f);
    	sf::Vector2f size;
private:
	std::vector<Drawn*> parts;
};

#endif