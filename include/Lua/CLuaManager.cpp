/*
 * CLuaManager.cpp
 *
 *  Created on: 28-ago-2008
 *      Author: 79481180
 */
#include <sstream>

#include "CLuaManager.h"

#include <luabind/class_info.hpp>

int add_file_and_line( lua_State* L )
{

  lua_Debug d;
  lua_getstack( L,
                1,
                &d );
  lua_getinfo( L,
               "Sln",
               &d );
  std::string err = lua_tostring(L, -1);
  lua_pop( L,
           1 );
  std::stringstream msg;
  msg << "\n" << d.short_src << ":" << d.currentline;

  if ( d.name != 0 ) {
    msg << "(" << d.namewhat << " " << d.name << ")";
  }
  msg << " " << err;
  lua_pushstring( L,
                  msg.str().c_str() );
  fprintf( stderr,
           msg.str().c_str() );
  return 1;

}

CLuaManager::CLuaManager()
{

  Lua = lua_open();
  luaL_openlibs( Lua );
  luabind::open( Lua ); // Connect LuaBind to this lua state
  luabind::set_pcall_callback( &add_file_and_line );
  //	luabind::bind_class_info( Lua );

}

CLuaManager::~CLuaManager()
{
  lua_close( Lua );
}
void CLuaManager::RunLuaDoFile( const std::string& script_name )
{

  if ( luaL_dofile(Lua, script_name.c_str()) != 0 ) {

    throw( luabind::error( Lua ) );

  }

}
void CLuaManager::RunLuaDoString( const std::string& thestring )
{
  if ( luaL_dostring(Lua, thestring.c_str()) != 0 ) {

    throw( luabind::error( Lua ) );
  }
}
