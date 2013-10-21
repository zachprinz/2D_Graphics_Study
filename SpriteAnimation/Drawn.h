#ifndef DRAWN_H
#define DRAWN_H

#include <vector>
#include <SFML/Graphics.hpp>

class Drawn
{
public:
	Drawn(std::string);
	Drawn(sf::Texture);
	Drawn();
	bool GetVisible();
	sf::Sprite* GetSprite();
	sf::Vector2f GetPositionOnPanel();
	virtual void Update(sf::RenderTexture&);
	virtual void OnClick();
	virtual void OnRClick(sf::Vector2i);
	virtual void OnHover(bool);
	void Move(float,float);
	void SetLocation(float,float);
	static sf::IntRect GetTextureFromAtlas(std::string);
	sf::IntRect texturePart;
	static sf::Texture gameTexture;
protected:
	void MoveOnGrid(int,int);
	bool isVisible;
	sf::Texture texture;
	sf::Texture myTexture;
	sf::Sprite sprite;
	sf::Vector2f positionOnPanel;
};

#endif