#define _USE_MATH_DEFINES
#include "LightObject.h"
#include "SpritePanel.h"
#include <cmath>
#include <math.h>

std::vector<int> LightObject::tags;

LightObject::LightObject(int x,int y,tmx::MapObject* obj) : AmbienceObject(x,y,obj,true){

};
void LightObject::Update(sf::RenderTexture& panel){
	AmbienceObject::Update(panel);
};