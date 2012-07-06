/*
 * MyGame.cpp
 *
 *  Created on: 12-mar-2009
 *      Author: 79481180
 */
#include "mygame.h"

#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include <misc/debug.h>
#include <misc/Log.h>
#include <misc/Interface.h>
#include <Lua/CLuaManager.h>

#include "param.h"
#include "registertolua.h"

MyGame::MyGame()
{
}
MyGame::~MyGame()
{
}

void MyGame::Init( const std::string& config )
{
  GameEngine::Init();
  InitParam( config );
  InitInterface();
  InitLua();

}

void MyGame::Cleanup()
{
  GameEngine::Cleanup();

}

Interface& MyGame::interface() const
{
  return *interface_;
}
Param& MyGame::param() const
{
  return *param_;
}
//------------------------------------------------------------------------------
// Procedimientos privados.
//------------------------------------------------------------------------------
void MyGame::InitParam( const std::string& config )
{
  Param* p = new Param( config );
  param_.reset( p );
}
void MyGame::InitInterface()
{

  Interface::ScreenResolutionType res( param().screen.resolution,
                                       param().screen.full );
  Interface* i = new Interface( param().screen.icon,
                                param().screen.font,
                                res );
  interface_.reset( i );

}
void MyGame::InitLua()
{

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
