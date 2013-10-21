#include "Label.h"
#include <iostream>

std::vector<sf::Font> Label::fonts;

Label::Label(int x,int y,sf::Texture texture, Fonts font, std::string str) : GuiElement(x,y,texture){
	text.setFont(fonts[font]);
	text.setCharacterSize(22);
	text.setString(str);
	sprite.setScale(text.getLocalBounds().width / sprite.getLocalBounds().width, 1);
	text.setPosition(x,y);
	text.setColor(sf::Color::White);
};
Label::Label(int x,int y,std::string texture, Fonts font, std::string str) : GuiElement(x,y,texture){
	text.setFont(fonts[font]);
	text.setCharacterSize(22);
	text.setString(str);
	sprite.setScale(text.getLocalBounds().width / sprite.getLocalBounds().width, 1);
	text.setPosition(x,y);
	text.setColor(sf::Color::White);
};
Label::Label(int x,int y,int textureLength,sf::Texture texture, Fonts font, std::string str) : GuiElement(x,y,texture){
	text.setFont(fonts[font]);
	text.setCharacterSize(22);
	sprite.setScale(((float)textureLength)/sprite.getLocalBounds().width,1);
	text.setPosition(x,y);
	text.setColor(sf::Color::White);
	text.setString(str);
};
Label::Label(int x,int y,int textureLength,std::string texture, Fonts font, std::string str) : GuiElement(x,y,texture){
	text.setFont(fonts[font]);
	text.setCharacterSize(22);
	sprite.setScale(((float)textureLength)/sprite.getLocalBounds().width,1);
	text.setPosition(x,y);
	text.setColor(sf::Color::White);
	text.setString(str);
};
void Label::SetText(sf::Text t){
	text = t;
};
sf::Text* Label::GetText(){
	return &text;
};
void Label::Update(sf::RenderTexture& panel){
	panel.draw(sprite);
	panel.draw(text);
};
void Label::OnStart(){
	sf::Font fontA;
	fontA.loadFromFile("gamefont.ttf");
	fonts.push_back(fontA);
}
void Label::SetLocation(float x, float y){
	text.setPosition(x,y);
	GuiElement::SetLocation(x,y);
}
void Label::SetTextOffset(float x,float y){
	text.setPosition(text.getPosition().x + x,text.getPosition().y + y);
}
void Label::SetTextColor(sf::Color newColor){
	text.setColor(newColor);
};
void Label::CenterText(){
	text.setPosition(sprite.getGlobalBounds().left + ((sprite.getGlobalBounds().width - text.getGlobalBounds().width) / 2),text.getPosition().y);
};
void Label::SetText(std::string str){
	text.setString(str + "");
};
