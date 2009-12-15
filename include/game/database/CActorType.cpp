/*
 * CActorType.cpp
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */
#include "CActorType.h"

#include <tinyxml.h>

#include <game/GameException.h>
#include <Lua/CLuaManager.h>

#include "CPersonality.h"
#include "CActorManager.h"

bool CActorType::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	THROW_GAME_EXCEPTION_IF(!(pXMLData->Attribute("script")),"Error m_LuaScript ActorType no definido" );
	std::string luaScript( pXMLData->Attribute( "script" ) );

	TiXmlElement *pPersonality = NULL;
	pPersonality = pXMLData->FirstChildElement( "Personality" );
	while ( pPersonality ) {

		CPersonality_ptr personality( new CPersonality() );
		THROW_GAME_EXCEPTION_IF(!pPersonality->Attribute("name"),"Error Name Personality no definido");
		std::string name( pPersonality->Attribute( "name" ) );

		if ( personality->Load( pPersonality ) == false ) return false;
		m_mPersonality[name] = personality;
		// Añadir a los estados del actor el nuevo estado.
		pPersonality = pPersonality->NextSiblingElement( "Personality" );

	}
	//
	// Se ha de ejecutar despues de registrar las funciones lua.
	//
	LuaManager.RunLuaDoFile( luaScript );
	return true;

}

bool CActorType::PersonalityExist( const std::string& personality ) const {

	return m_mPersonality.find( personality ) != m_mPersonality.end();

}
const CPersonality* CActorType::GetPersonality( const std::string& personality ) {

	THROW_GAME_EXCEPTION_IF(!PersonalityExist(personality),"Error GetPersonality personality no definido ");
	return m_mPersonality[personality].get();

}
