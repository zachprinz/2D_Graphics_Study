#include "ScriptManager.h"
#include "Item.h"

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"
}
#include <luabind/luabind.hpp>
#include <iostream>
#include "LevelSet.h"

#pragma comment(lib, "C:/Misc/luabind/msvc-11.0-x86/luabindBuild.lib")
#pragma comment(lib, "C:/Misc/lua/msvc-11.0-x86/lua.lib")


using namespace luabind;

lua_State* ScriptManager::L_;

void ScriptManager::InitiateLuaBind(){
	L_ = luaL_newstate();
	luabind::open(L_);
    lua_register( L_, "_ALERT", lua_error );
	luaopen_base(L_);
	luaopen_string(L_);
};
void ScriptManager::CreateBinds(){
	luabind::module(L_)
    [
        class_<Item>("Item")
		.def_readwrite("slot", &Item::slot)
		.def_readwrite("name", &Item::name)
		.def_readwrite("itemLevels",&Item::itemLevels)
    ];
	luabind::module(L_)
    [
        class_<LevelSet>("LevelSet")
		.def("SetLevels", &LevelSet::SetLevels)
    ];
	luabind::module(L_)
    [
        class_<Enemy>("Enemy")
		.def("SetName", &Enemy::SetName)
		.def("AddDrop", &Enemy::AddDrop)
    ];
};
void ScriptManager::CreateItem(std::string id,Item* item){
	luaL_dofile(L_,"scripts/items.lua");
	luabind::globals(L_)["instanceItem"] = item;
	luabind::globals(L_)["instanceItemLevels"] = &(item->itemLevels);
	std::string itemName = "item" + id;
	try {
		luabind::call_function<void>(L_, "createItem",itemName);
	} catch (luabind::error& e) {
		std::string error = lua_tostring(e.state(), -1);
		std::cout << error << std::endl;
	}
};
void ScriptManager::CreateEnemy(std::string name,Enemy* enemy){
	luaL_dofile(L_,"scripts/enemy.lua");
	luabind::globals(L_)["instanceEnemy"] = enemy;
	std::string enemyName = name;
	try {
		luabind::call_function<void>(L_, "createEnemy",enemyName);
	} catch (luabind::error& e) {
		std::string error = lua_tostring(e.state(), -1);
		std::cout << error << std::endl;
	}
};