#ifndef SLICEDSPRITECREATOR_H
#define SLICEDSPRITECREATOR_H

#include <vector>
#include <SFML/Graphics.hpp>

class SlicedSpriteCreator
{
public:
	static std::vector<std::vector<sf::IntRect>> spriteParts;
	static std::vector<std::vector<sf::IntRect>> scrollBarParts;
	static enum Parts {TopLeft,Top,TopRight,Left,Center,Right,BottomLeft,Bottom,BottomRight};
	static enum SpriteStyle {Pixel,WoodPanel,TextPanel,Last};
	static sf::Texture GetSlicedTexture(float,float,SpriteStyle);
	static sf::Texture GetSlicedScrollBar(float);
	static void OnStart();
private:
};

#endif