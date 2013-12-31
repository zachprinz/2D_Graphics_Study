#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "Bar.h"

class ScrollBar : public Bar
{
public:
    ScrollBar(int x, int y, int length, float* percent);
    void SetVerticle();
    void SetHorizontle();
    void Update(GamePanel*);
private:
	bool isHorizontle;
	bool isVerticle;
	sf::Vector2f oPos;
};
#endif