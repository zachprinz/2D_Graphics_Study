#include "CheckBox.h"

CheckBox::CheckBox(bool* bl, int x, int y, std::string background, std::string foreground) : GuiElement(x,y,background,foreground){
    myBool = bl;
};
CheckBox::CheckBox(bool* bl, int x, int y) : GuiElement(x,y,"checkbox.png","check.png"){
    myBool = bl;
};
void CheckBox::Update(GamePanel* panel){
    Draw(panel);
    if(myBool)
	foreground->Draw(panel);
};
void CheckBox::OnClick(){
	(*myBool) = (!(*myBool));
};
void CheckBox::OnHover(bool hovered){
	if(hovered){
	    foreground->ExpandBy(1.075,sf::seconds(0.1));
	}
	else{
	    foreground->ReturnExpand();
	}
};
void CheckBox::SetScale(float x, float y){
    
};