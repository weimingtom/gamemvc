/*
 * CLuaManager.h
 *
 *  Created on: 28-ago-2008
 *      Author: 79481180
 */

#ifndef CLUAMANAGER_H_
#define CLUAMANAGER_H_

#include <string>
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include <misc/singleton.hpp>

int add_file_and_line( lua_State* L );

#define LuaManager	Singleton<CLuaManager>::Instance()

class CLuaManager
{
  public:
    CLuaManager();
    virtual ~CLuaManager();

    lua_State* GetLua()
    {
      return Lua;
    }
    void RunLuaDoFile( const std::string& script_name );
    void RunLuaDoString( const std::string& thestring );

  private:
    lua_State* Lua;
};

#endif /* CLUAMANAGER_H_ */
