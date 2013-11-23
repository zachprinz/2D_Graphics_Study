#define _USE_MATH_DEFINES
#include "LightObject.h"
#include "SpritePanel.h"
#include <cmath>
#include <math.h>

std::vector<int> LightObject::tags;

LightObject::LightObject(int x,int y,tmx::MapObject* obj) : AmbienceObject(x,y,obj,true){
	myLight = new Light((x*32) + 16,(y*32) + 48,sf::Color(248,255,127),150,1.0f,75); //Need to check and send the correct height, not just 75.
	SpritePanel::instance->AddLight(this);
};
void LightObject::Update(sf::RenderTexture& panel){
	AmbienceObject::Update(panel);
};
Light* LightObject::getLight(){
	return myLight;
}