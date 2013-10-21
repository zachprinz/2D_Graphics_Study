#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}
#include <luabind/luabind.hpp>
#include <iostream>
#include "Enemy.h"

#pragma comment(lib, "C:/Misc/luabind/msvc-11.0-x86/luabindBuild.lib")
#pragma comment(lib, "C:/Misc/lua/msvc-11.0-x86/lua.lib")

class Item;
class ScriptManager
{
public:
	static void InitiateLuaBind();
	static void CreateBinds();
	static void CreateItem(std::string id, Item*);
	static void CreateEnemy(std::string name, Enemy*);
	static lua_State* L_;
private:

};

#endif