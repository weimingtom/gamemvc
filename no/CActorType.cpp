/*
 * CActorType.cpp
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */
#include "CActorType.h"

#include <tinyxml.h>

#include <sstream>

#include "game/GameException.h"
#include <gameengine/CGameEngine.h>
#include <misc/utils.h>

#include "Lua/CLuaManager.h"

#include "CPersonality.h"
#include "CActorManager.h"


CActorType::~CActorType(){

	DeleteSTLMap(m_mPersonality);

}

bool CActorType::Load(TiXmlElement* pXMLData) {

	if (!pXMLData)
		return false;

	THROW_GAME_EXCEPTION_IF(!(pXMLData->Attribute("name")),"Error Name ActorType no definido");
	m_Name = pXMLData->Attribute("name");

	THROW_GAME_EXCEPTION_IF(!(pXMLData->Attribute("script")),"Error m_LuaScript ActorType no definido" );
	string luaScript = pXMLData->Attribute("script");

	TiXmlElement *pPersonality = NULL;
	pPersonality = pXMLData->FirstChildElement("Personality");
	while (pPersonality) {

		CPersonality* personality = new CPersonality();

		if (personality->Load(pPersonality) == false)
			return false;

		// Aadir a los estados del actor el nuevo estado.
		m_mPersonality[personality->GetNamePersonality()] = personality;
		pPersonality = pPersonality->NextSiblingElement("Personality");

	}
	//
	// Se ha de ejecutar despues de registrar las funciones lua.
	//
	LuaManager->RunLuaDoFile(luaScript.c_str());
	return true;

}

string CActorType::GetNameActorType() {

	return m_Name;

}

CPersonality* CActorType::GetPersonality(string personality) {

	return m_mPersonality[personality];

}
