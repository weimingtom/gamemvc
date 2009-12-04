/*
 * CActorManager.h
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */

#ifndef CACTORMANAGER_H_
#define CACTORMANAGER_H_

#include <tinyxml.h>

#include <string>
#include <map>

#include <lua.hpp>

#include <misc/singleton.hpp>

class CGameEngine;
class CActorType;

#define ActorManager	Singleton<CActorManager>::Instance()
class CActorManager
{
public:

	~CActorManager();
	bool Load( TiXmlElement* pXMLData );
	bool ActorExist( const std::string& elActor );
	CActorType* GetActorType( const std::string& elActor );
	CGameEngine* GetGame();

private:

	map < std::string, CActorType* > m_mActorManager;

};

#endif /* CACTORMANAGER_H_ */
