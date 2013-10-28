#include "ProgressBar.h"
#include <iostream>

sf::Texture ProgressBar::blankText;
sf::Texture ProgressBar::backgroundLeft;
sf::Texture ProgressBar::backgroundRight;
sf::Texture ProgressBar::backgroundCenter;
sf::Texture ProgressBar::foregroundCenter;

sf::Texture ProgressBar::CreateBackground(int length){
	sf::RenderTexture background;
	background.create(length,25);
	sf::Sprite backgroundSprite;
	sf::Sprite tempSprite;
	sf::Texture tempText = CreateTiledTexture(length - 50,backgroundCenter);
	backgroundSprite.setTexture(tempText);
	backgroundSprite.setPosition(25,0);
	background.draw(backgroundSprite);

	tempSprite.setTexture(backgroundLeft);
	tempSprite.setPosition(0,0);
	background.draw(tempSprite);
	tempSprite.setTexture(backgroundRight);
	tempSprite.setPosition(length - 25,0);
	background.draw(tempSprite);
	background.display();
	return background.getTexture();
};

sf::Texture ProgressBar::CreateTiledTexture(int length, sf::Texture text){
	int leftover = length % text.getSize().x;
	int fit = length / text.getSize().x;
	float each = ((float)leftover) / ((float) fit);
	sf::Sprite tempSprite;
	tempSprite.setTexture(text);
	tempSprite.setScale((each + tempSprite.getLocalBounds().width) / tempSprite.getLocalBounds().width,1);
	sf::RenderTexture tiled;
	tiled.create(length,25);
	for(int x = 0; x < fit + 1; x++){
		tempSprite.setPosition(x * tempSprite.getLocalBounds().width,0);
		tiled.draw(tempSprite);
	}
	tiled.display();
	return tiled.getTexture();
};

ProgressBar::ProgressBar(float* percent,sf::Sprite* relative) : GuiElement(0,0,blankText){
	this->percent = percent;
	this->relative = relative;
	background = sf::RectangleShape(sf::Vector2f(26,2));
	background.setFillColor(sf::Color(255,0,0,255));
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(1);
	foregroundRect = sf::RectangleShape(sf::Vector2f(26,2));
	foregroundRect.setFillColor(sf::Color(0,255,0,255));
	foregroundRect.setOutlineColor(sf::Color::Black);
	foregroundRect.setOutlineThickness(1);
	foregroundRect.setScale(*percent,1.f);
	fg = &foregroundRect;
	stationary = false;
};
ProgressBar::ProgressBar(int x, int y, int length, float* percent) : GuiElement(x,y,CreateBackground(length),CreateTiledTexture(length - 50,foregroundCenter)){
	foreground->GetSprite()->setPosition(x + 25,y);
	fg = &(foregroundRect);
	this->percent = percent;
	stationary = true;
};
ProgressBar::ProgressBar() : GuiElement(0,0,blankText) {

};
void ProgressBar::Update(sf::RenderTexture& panel){
	if(!stationary){
		if(percent > 0)
			foregroundRect.setScale(*percent,1.f);
		SetBarPosition(sf::Vector2f(relative->getPosition().x + 4,relative->getPosition().y - foregroundRect.getSize().y));
		panel.draw(background);
		panel.draw(foregroundRect);
	}
	else{
		if(percent > 0){
			foreground->GetSprite()->setTextureRect(sf::IntRect(0,0,foreground->GetSprite()->getTexture()->getSize().x * (*percent),25));
		}
		panel.draw(sprite);
		panel.draw(*foreground->GetSprite());
	}
};
float ProgressBar::GetPercent(){
	return *percent;
};
void ProgressBar::SetUp(){
	blankText.loadFromFile("blank.png");
	backgroundLeft.loadFromFile("progressbar/background/0.png");
	backgroundCenter.loadFromFile("progressbar/background/1.png");
	backgroundRight.loadFromFile("progressbar/background/2.png");
	foregroundCenter.loadFromFile("progressbar/foreground/0.png");
};
void ProgressBar::SetBarPosition(sf::Vector2f pos){
	if(!stationary){
		background.setPosition(pos);
		foregroundRect.setPosition(pos);
	}
	else{
		sprite.setPosition(pos);
		foreground->GetSprite()->setPosition(sf::Vector2f(pos.x + 25,pos.y));
	}
};
void ProgressBar::SetPercent(float* newPercent){
	percent = newPercent;
};