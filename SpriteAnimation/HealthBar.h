#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Bar.h"

class HealthBar : public Bar
{
public:
    HealthBar(float* percent, sf::Sprite* relative);
    void Update(GamePanel* panel);
    void SetBarPosition(sf::Vector2f);
    sf::RectangleShape foregroundRect;
    sf::RectangleShape backgroundRect;
    sf::Sprite* relative;
private:

};
#endif