#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "GuiElement.h"

class CheckBox : public GuiElement
{
public:
    CheckBox(bool*,int,int,std::string,std::string);
    CheckBox(bool*,int,int);
    void Update(GamePanel*);
    void OnClick();
    void SetScale(float,float);
    void OnHover(bool);
    //void SetMoveOnHover(bool);
    //void SetHoverMovePosition(sf::Vector2f);
protected:
    bool* myBool;
};
#endif