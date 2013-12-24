#ifndef BAR_H
#define BAR_H

#include "GuiElement.h"

class Bar : public GuiElement
{
public:
    Bar(int x, int y, float* percent,int length, std::string bg, std::string fg);
    Bar(int x, int y, float* percent,int length, SlicedSprite* bg, std::string fg);
    virtual void Update(GamePanel*);
    void SetPercent(float*);
    virtual void SetBarPosition(sf::Vector2f);
    float GetPercent();
protected:
    int fullscale;
    float* percent;
    sf::Vector2i offset;
};
#endif