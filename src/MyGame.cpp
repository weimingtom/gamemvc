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

#include "CParam.h"
#include "RegisterToLua.h"

MyGame::MyGame() {
}
MyGame::~MyGame() {
}

void MyGame::Init( const std::string& config ) {
    CGameEngine::Init();

    InitParam( config );
    InitInterface();
    InitLua();

    L_(debug)
<<    "MyGame::Init";
}

void MyGame::Cleanup() {
    CGameEngine::Cleanup();

    L_(debug)
<<    "MyGame::Cleanup";
}
Interface& MyGame::interface() const {
    return *m_interface_;
}
//------------------------------------------------------------------------------
// Procedimientos privados.
//------------------------------------------------------------------------------
void MyGame::InitParam( const std::string& config ) {
    pt::ptree pt;
    pt::read_ini( config,
                  pt );

    param.screen.resolution = pt.get < std::string > ( "screen.resolution",
                                                       "SMALL" );

    param.screen.full = pt.get( "screen.fullscreen",
                                false );
    param.screen.icon = pt.get < std::string > ( "screen.icon" );
    param.screen.font = pt.get < std::string > ( "screen.font" );
    param.gamedata = pt.get < std::string > ( "game.gamedata" );
    param.lua = pt.get < std::string > ( "game.lua" );
}
void MyGame::InitInterface() {
    Interface::ScreenResolutionType res( param.screen.resolution,
                                         param.screen.full );
    m_interface_.reset( new Interface( param.screen.icon,
                                      param.screen.font,
                                      res ) );
}
void MyGame::InitLua() {
    LuaManager.RunLuaDoFile( param.lua );

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
