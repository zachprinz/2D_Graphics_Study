#ifndef LEVELSET_H
#define LEVELSET_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <map>

class LevelSet
{
public:
	LevelSet(int str,int end,int speedA,int tech,int mine, int wc,int smith,int craft);
	LevelSet();
	void ClearStats();
	LevelSet AddLevelSet(LevelSet levelSet);
	void SetLevels(int str,int end,int speedA,int tech,int mine, int wc,int smith,int craft);
	void SetLevelsDoubles(double str,double end,double speedA,double tech,double mine, double wc,double smith,double craft);
    int strength;
    int endurance;
    int speed;
    int technique;
    int mining;
    int woodcutting;
    int smithing;
    int crafting;
private:

};

#endif