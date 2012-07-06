/*
 * RegisterToLua.h
 *
 *  Created on: 04-ago-2008
 *      Author: 79481180
 */

#ifndef REGISTERTOLUA_H_
#define REGISTERTOLUA_H_

#include <luabind/luabind.hpp>
#include <luabind/adopt_policy.hpp>
using namespace luabind;

void RegisterToLuaTelegram( lua_State* Lua );
void RegisterToLuaMessageDispacher( lua_State* Lua );
void RegisterToLuaCrudeTimer( lua_State* Lua );
void RegisterToLuaVector2D( lua_State* Lua );
void RegisterToLuaModel( lua_State* Lua );
void RegisterToLuaGameWorld( lua_State* Lua );
void RegisterToLuaBaseGameEntity( lua_State* Lua );
void RegisterToLuaMovingEntity( lua_State* Lua );
void RegisterToLuaSteeringBehavior( lua_State* Lua );
//
void RegisterToLuaGoal( lua_State* Lua );
void RegisterToLuaActorMapa( lua_State* Lua );
void RegisterToLuaCActorType( lua_State* Lua );
void RegisterToLuaCActor_PathPlanner( lua_State* Lua );

#endif /* REGISTERTOLUA_H_ */
