#ifndef SCRIPTOR_H
#define SCRIPTOR_H
//-----------------------------------------------------------------------------
//
//  Name:   Scriptor.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class encapsulating the basic functionality necessary to read a
//          Lua config file
//-----------------------------------------------------------------------------

#include "lua.hpp"

#include "Lua/luahelperfunctions.h"

class Scriptor
{

  public:

    Scriptor()
        : m_pLuaState( luaL_newstate() )
    {
      //open the libraries
      luaL_openlibs( m_pLuaState );
    }

    ~Scriptor()
    {
      lua_close( m_pLuaState );
    }

    void RunScriptFile( const char* ScriptName )
    {
      RunLuaScript( m_pLuaState,
                    ScriptName );
    }

    lua_State* GetState()
    {
      return m_pLuaState;
    }

    int GetInt( const char* VariableName )
    {
      return PopLuaNumber < int >( m_pLuaState,
                                   VariableName );
    }

    double GetFloat( const char* VariableName )
    {
      return PopLuaNumber < float >( m_pLuaState,
                                     VariableName );
    }

    double GetDouble( const char* VariableName )
    {
      return PopLuaNumber < double >( m_pLuaState,
                                      VariableName );
    }

    std::string GetString( const char* VariableName )
    {
      return PopLuaString( m_pLuaState,
                           VariableName );
    }

    bool GetBool( const char* VariableName )
    {
      return PopLuaBool( m_pLuaState,
                         VariableName );
    }

  private:

    lua_State* m_pLuaState;

};

#endif

