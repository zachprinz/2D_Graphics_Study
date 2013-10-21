#include "LevelSet.h"

LevelSet::LevelSet(int str,int end,int speedA,int tech,int mine, int wc,int smith,int craft){
	strength = str;
    endurance = end;
    speed = speedA;
    technique = tech;
    mining = mine;
    woodcutting = wc;
    crafting = craft;
    smithing = smith;
};
LevelSet::LevelSet(){
	strength = 0;
    endurance = 0;
    speed = 0;
    technique = 0;
    mining = 0;
    woodcutting = 0;
    smithing = 0;
    crafting = 0;
};
void LevelSet::ClearStats(){
	strength = 0;
    endurance = 0;
    speed = 0;
    technique = 0;
    mining = 0;
    woodcutting = 0;
    crafting = 0;
    smithing = 0;
};
LevelSet LevelSet::AddLevelSet(LevelSet levelSet){
	       return LevelSet(strength + levelSet.strength, endurance + levelSet.endurance, speed + levelSet.speed, technique + levelSet.technique, mining + levelSet.mining, woodcutting + levelSet.woodcutting,0,0);
};
void LevelSet::SetLevels(int str,int end,int speedA,int tech,int mine, int wc,int smith,int craft){
	strength = str;
    endurance = end;
    speed = speedA;
    technique = tech;
    mining = mine;
    woodcutting = wc;
    crafting = craft;
    smithing = smith;
};
void LevelSet::SetLevelsDoubles(double str,double end,double speedA,double tech,double mine, double wc,double smith,double craft){
	strength = str;
    endurance = end;
    speed = speedA;
    technique = tech;
    mining = mine;
    woodcutting = wc;
    crafting = craft;
    smithing = smith;
};
