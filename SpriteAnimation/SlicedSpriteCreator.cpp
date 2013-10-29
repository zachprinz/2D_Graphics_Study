#include "SlicedSpriteCreator.h"
#include <iostream>
#include "Drawn.h"

std::vector<std::vector<sf::IntRect>> SlicedSpriteCreator::spriteParts;
std::vector<std::vector<sf::IntRect>> SlicedSpriteCreator::scrollBarParts;

sf::Texture SlicedSpriteCreator::GetSlicedTexture(float x,float y,SlicedSpriteCreator::SpriteStyle style){
	sf::RenderTexture slicedSprite;
	slicedSprite.create(x,y);
	slicedSprite.clear(sf::Color(0,0,0,0));
	std::vector<sf::IntRect> textParts = spriteParts[style];
	std::vector<sf::Sprite> parts;
	for(int x = 0; x < textParts.size(); x++){
		sf::Sprite temp;
		temp.setTexture(Drawn::gameTexture);
		temp.setTextureRect(textParts[x]);
		parts.push_back(temp);
	}
	float topLength = x - (textParts[0].width + textParts[2].width);
	parts[1].setScale(topLength / textParts[1].width,1);
	parts[4].setScale(topLength / textParts[1].width,1);
	parts[7].setScale(topLength / textParts[1].width,1);
	float sideHeight = y - (textParts[0].height + textParts[6].height);
	parts[3].setScale(parts[3].getScale().x,sideHeight / textParts[3].height);
	parts[4].setScale(parts[4].getScale().x,sideHeight / textParts[3].height);
	parts[5].setScale(parts[5].getScale().x,sideHeight / textParts[3].height);
	std::cout << "X Scale: " << std::to_string(parts[4].getScale().x) << " Y Scale: " << std::to_string(parts[4].getScale().y) << std::endl;
	parts[0].setPosition(0,0);
	parts[1].setPosition(parts[0].getGlobalBounds().width,0);
	parts[2].setPosition(parts[1].getGlobalBounds().width + parts[2].getGlobalBounds().width,0);
	parts[3].setPosition(0,parts[0].getGlobalBounds().height);
	parts[4].setPosition(parts[3].getGlobalBounds().width, parts[0].getGlobalBounds().height);
	parts[5].setPosition(parts[3].getGlobalBounds().width + parts[4].getGlobalBounds().width,parts[2].getGlobalBounds().height);
	parts[6].setPosition(0,parts[0].getGlobalBounds().height + parts[3].getGlobalBounds().height);
	parts[7].setPosition(parts[6].getGlobalBounds().width,parts[0].getGlobalBounds().height + parts[3].getGlobalBounds().height);
	parts[8].setPosition(parts[6].getGlobalBounds().width + parts[7].getGlobalBounds().width,parts[0].getGlobalBounds().height + parts[3].getGlobalBounds().height);
	for(int x = 0; x < parts.size(); x++){
			slicedSprite.draw(parts[x]);
	}
	slicedSprite.display();
	std::cout << "New Sliced Sprite " << std::to_string(slicedSprite.getSize().x) << "," << std::to_string(slicedSprite.getSize().y) << std::endl;
	return slicedSprite.getTexture();
};

sf::Texture SlicedSpriteCreator::GetSlicedScrollBar(float y){
	sf::RenderTexture slicedSprite;
	slicedSprite.create(24,y);
	slicedSprite.clear(sf::Color(0,0,0,0));
	std::vector<sf::IntRect> textParts = scrollBarParts[0];
	std::vector<sf::Sprite> parts;
	for(int x = 0; x < textParts.size(); x++){
		sf::Sprite temp;
		temp.setTexture(Drawn::gameTexture);
		temp.setTextureRect(textParts[x]);
		parts.push_back(temp);
	}
	float sideHeight = y - (textParts[0].height + textParts[2].height);
	parts[1].setScale(parts[1].getScale().x,sideHeight / textParts[1].height);
	parts[0].setPosition(0,0);
	parts[1].setPosition(0,parts[0].getGlobalBounds().height);
	parts[2].setPosition(0,parts[0].getGlobalBounds().height + parts[1].getGlobalBounds().height);
	for(int x = 0; x < parts.size(); x++){
			slicedSprite.draw(parts[x]);
	}
	slicedSprite.display();
	std::cout << "New Sliced Scrollbar " << std::to_string(slicedSprite.getSize().x) << "," << std::to_string(slicedSprite.getSize().y) << std::endl;
	return slicedSprite.getTexture();
};

void SlicedSpriteCreator::OnStart(){
	for(int x = 0; x < Last; x++){
		std::vector<sf::IntRect> tempTexts;
		for(int y = 0; y < 9; y++){
			sf::Texture tempText;
			tempTexts.push_back(Drawn::GetTextureFromAtlas("slicedsprites/" + std::to_string(x) + "/" + std::to_string(y) + ".png"));
		}
		spriteParts.push_back(tempTexts);
	}
	for(int x = 0; x < 1; x++){
		std::vector<sf::IntRect> tempTexts;
		for(int y = 0; y < 3; y++){
			sf::Texture tempText;
			tempTexts.push_back(Drawn::GetTextureFromAtlas("slicedsprites/scrollBar/" + std::to_string(x) + "/" + std::to_string(y) + ".png"));
		}
		scrollBarParts.push_back(tempTexts);
	}
};
