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
using namespace std;

#include <lua.hpp>

#include <misc/Singleton.h>

class CGameEngine;
class CActorType;

#define ActorManager	Singleton<CActorManager>::GetSingletonPtr()
class CActorManager
{
public:

	~CActorManager();
	bool Load(TiXmlElement* pXMLData);
	bool ActorExist(string elActor);
	CActorType* GetActorType(string elActor);
	CGameEngine* GetGame();

private:

	map<string , CActorType*> m_mActorManager;

};

#endif /* CACTORMANAGER_H_ */
