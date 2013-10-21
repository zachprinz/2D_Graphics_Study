#ifndef SLICEDSPRITECREATOR_H
#define SLICEDSPRITECREATOR_H

#include <vector>
#include <SFML/Graphics.hpp>

class SlicedSpriteCreator
{
public:
	static std::vector<std::vector<sf::IntRect>> spriteParts;
	static enum Parts {TopLeft,Top,TopRight,Left,Center,Right,BottomLeft,Bottom,BottomRight};
	static enum SpriteStyle {Pixel,WoodPanel,Last};
	static sf::Texture GetSlicedTexture(float,float,SpriteStyle);
	static void OnStart();
private:
};

#endif