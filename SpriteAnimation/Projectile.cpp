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
};

void Projectile::Update(GamePanel* panel){
	if(isVisible = true){
		std::vector<RoomTile*> directionalTiles = GetDirectionalRoomTiles(projectileVelocity.x / std::abs(projectileVelocity.x),projectileVelocity.y / std::abs(projectileVelocity.y));
		std::vector<RoomTile*> ocupiedTiles;
		for(int x = 0; x < 4; x++){
			if(directionalTiles[x]->GetOcupied())
				ocupiedTiles.push_back(directionalTiles[x]);
		}
		SetPosition(GetPosition() + sf::Vector2f(projectileVelocity.x * projectileClock.getElapsedTime().asSeconds(), projectileVelocity.y * projectileClock.restart().asSeconds()));
		sf::Vector2f tempVec = orginPosition - sprite.getPosition();
		float totalDistance = std::sqrt(std::pow(tempVec.x,2.0) + std::pow(tempVec.y,2.0));
		if(totalDistance > range)
			Destroy();
		else{
			UpdateRoomTile();
			CheckForCollision(ocupiedTiles);
		}
		GameSprite::Update(panel);
	}
};

bool Projectile::CheckForCollision(std::vector<RoomTile*> tiles){
	for(int x = 0; x < tiles.size(); x++){
		for(int y = 0; y < tiles[x]->ocupants.size(); y++){
			if(false){//SpritePanel::instance->room->GetOcupant(tiles[x]->ocupants[y])->GetBounds().Contains(GetBounds())){
				Hit(tiles[x]);
				Destroy();
				return true;
			}
		}
	}
	return false;
};

void Projectile::Destroy(){
	isVisible = false;
	SpritePanel::instance->room->RemoveOcupant(GetTag());
};

void Projectile::Hit(RoomTile* rt){

}