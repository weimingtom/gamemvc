/*
 * MyGame.cpp
 *
 *  Created on: 12-mar-2009
 *      Author: 79481180
 */
#include "MyGame.h"

#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <IsoHex/SdlException.hpp>
#include <misc/debug.h>
#include <misc/Log.h>
#include <misc/Interface.h>
#include <Lua/CLuaManager.h>

#include "Param.h"
#include "RegisterToLua.h"

MyGame::MyGame() {
}
MyGame::~MyGame() {
}

void MyGame::Init(const std::string& config) {
	CGameEngine::Init();

	InitParam( config );
	InitInterface();
	InitLua();

	L_(debug)
<<	"MyGame::Init";
}

void MyGame::Cleanup() {
	CGameEngine::Cleanup();

	L_(debug)
<<	"MyGame::Cleanup";
}
Interface& MyGame::interface() const {

	return *m_interface_;

}
Param& MyGame::param() const {
	return *m_param_;
}
//------------------------------------------------------------------------------
// Procedimientos privados.
//------------------------------------------------------------------------------
void MyGame::InitParam(const std::string& config) {

	m_param_.reset( new Param( config ) );
}
void MyGame::InitInterface() {
	Interface::ScreenResolutionType res( 	param().screen.resolution,
											param().screen.full );
	m_interface_.reset( new Interface( 	param().screen.icon,
										param().screen.font,
										res ) );
}
void MyGame::InitLua() {
	LuaManager.RunLuaDoFile( param().lua );

	RegisterToLuaCrudeTimer( LuaManager.GetLua() );
	RegisterToLuaVector2D( LuaManager.GetLua() );
	RegisterToLuaTelegram( LuaManager.GetLua() );
	RegisterToLuaCActorType( LuaManager.GetLua() );
	RegisterToLuaModel( LuaManager.GetLua() );
	RegisterToLuaGameWorld( LuaManager.GetLua() );
	RegisterToLuaBaseGameEntity( LuaManager.GetLua() );
	RegisterToLuaMovingEntity( LuaManager.GetLua() );
	RegisterToLuaActorMapa( LuaManager.GetLua() );
	RegisterToLuaGoal( LuaManager.GetLua() );
	RegisterToLuaSteeringBehavior( LuaManager.GetLua() );

	//  RegisterToLuaMessageDispacher(LuaManager.GetLua());
	//  RegisterToLuaScriptedStateMachine(LuaManager.GetLua());
	//  RegisterToLuaCTileMapa(LuaManager.GetLua());
	//  RegisterToLuaCActor_PathPlanner(LuaManager.GetLua());
}
