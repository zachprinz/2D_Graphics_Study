#define _USE_MATH_DEFINES
#include "LightObject.h"
#include "SpritePanel.h"
#include <cmath>
#include <math.h>

std::vector<int> LightObject::tags;

LightObject::LightObject(int x,int y,tmx::MapObject* obj) : AmbienceObject(x,y,obj,true){
	myLight = new Light(x,y,sf::Color(248,255,127),50,1.0f);
	SpritePanel::instance->AddLight(this);
};
void LightObject::Update(sf::RenderTexture& panel){
	AmbienceObject::Update(panel);
};
Light* LightObject::getLight(){
	return myLight;
}