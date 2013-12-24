#include "Bar.h"

Bar::Bar(int x, int y, float* percent,int length, std::string bg, std::string fg) : GuiElement(x,y,bg,fg){
    this->percent = percent;
    fullscale = length;
    offset = sf::Vector2i(0,0);
};

Bar::Bar(int x, int y, float* percent,int length, SlicedSprite* bg, std::string fg) : GuiElement(x,y,bg,fg){
    this->percent = percent;
    fullscale = length;
    offset = sf::Vector2i(0,0);
};

void Bar::Update(GamePanel* panel){

};

void Bar::SetPercent(float* percent){
    this->percent = percent;
};

float Bar::GetPercent(){
    return *percent;
};

void Bar::SetBarPosition(sf::Vector2f){

};