#include "ShadowLine.h"

ShadowLine::ShadowLine(sf::Vector2f first,sf::Vector2f second){
	firstPoint = first;
	secondPoint = second;
}; 
ShadowLine::ShadowLine(){

};
void ShadowLine::Draw(sf::RenderTexture* panel,sf::Vector2f pos){
	sf::Vertex line[] = {sf::Vertex(sf::Vector2f(firstPoint.x + pos.x - 11.2,firstPoint.y + pos.y + 9.6)),sf::Vertex(sf::Vector2f(secondPoint.x + pos.x - 11.2,secondPoint.y + pos.y+9.6))};
	panel->draw(line,2,sf::Lines);
}