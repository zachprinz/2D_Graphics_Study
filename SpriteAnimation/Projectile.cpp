#include "Projectile.h"
#include "SpritePanel.h"
#include "Combatant.h"

Projectile::Projectile(Combatant* owner, int x, int y, Attack myAttack,int angle,float range) : GameSprite(x,y,"arrow.png"){
	orginPosition = sf::Vector2f(x * 32,y*32);
	this->owner = owner;
	this->myAttack = myAttack;
	this->range = range;
	float speed = 400;
	if(angle == 90 || angle == 180 || angle == 0 || angle == 360 || angle == 270)
		angle += 1;
	if(angle > 360)
		angle = angle % 360;
	this->angle = ((float)angle) / 57.29f;
	projectileVelocity.y = std::sin(this->angle) * speed;
	projectileVelocity.x = std::cos(this->angle) * speed;
	UpdateRoomTile();
	hitting = true;
	SetRotation((90 + ((owner->currentAnimationPos.y % 4) * 90)) % 360);
	debugBox = sf::RectangleShape(sf::Vector2f(texturePart.width,texturePart.height));
	debugBox.setRotation(rotationAngle);
	debugBox.setFillColor(sf::Color(0,255,0,100));
};

void Projectile::Update(GamePanel* panel){
	if(isVisible = true){
		std::vector<RoomTile*> directionalTiles = GetDirectionalRoomTiles(projectileVelocity.x / std::abs(projectileVelocity.x),projectileVelocity.y / std::abs(projectileVelocity.y));
		std::vector<RoomTile*> ocupiedTiles;
		for(int x = 0; x < 4; x++){
			if(directionalTiles[x]->GetOcupied()){
				ocupiedTiles.push_back(directionalTiles[x]);
			}
		}
		SetPosition(GetPosition() + sf::Vector2f(projectileVelocity.x * projectileClock.getElapsedTime().asSeconds(), projectileVelocity.y * projectileClock.restart().asSeconds()));
		sf::Vector2f tempVec = orginPosition - sprite.getPosition();
		float totalDistance = std::sqrt(std::pow(tempVec.x,2.0) + std::pow(tempVec.y,2.0));
		if(totalDistance > range)
			Destroy();
		else{
			UpdateRoomTile();
			if(hitting)
				Hit(GetRoomTile());
			CheckForCollision(ocupiedTiles);
		}
		GameSprite::Update(panel);
		debugBox.setPosition(GetPosition());
		DrawOther(&debugBox,SpritePanel::instance);
	}
};

bool Projectile::CheckForCollision(std::vector<RoomTile*> tiles){
	std::vector<int> excludeTags;
	excludeTags.push_back(owner->GetTag());
	excludeTags.push_back(GetTag());
	for(int x = 0; x < tiles.size(); x++){
		std::vector<int> tileOcupants = tiles[x]->GetOcupantsBut(excludeTags);
		if(tileOcupants.size() > 0){
			if(tiles[x]->position.x == graphPositionA.x && tiles[x]->position.y == graphPositionA.y){
				if(hitting){
					Hit(tiles[x]);
					Destroy();
					return true;
				}
			}
		}
		else{
			hitting = !hitting;
		}
	}
	return false;
};

void Projectile::Destroy(){
	isVisible = false;
	SpritePanel::instance->room->RemoveOcupant(GetTag());
};

void Projectile::Hit(RoomTile* rt){
	owner->tileEffectFrameCount = 0;
	owner->nextAttackDamage = owner->SendDamage() * myAttack.damageModifier;
	owner->effectedTiles.push_back(sf::Vector2i(graphPositionA.x,graphPositionA.y));
}