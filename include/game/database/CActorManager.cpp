/*
 * ActorManager.cpp
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */
#include "CActorManager.h"

#include <tinyxml.h>

#include <game/GameException.h>

#include "CActorType.h"

bool CActorManager::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	TiXmlElement *pActorType = NULL;
	pActorType = pXMLData->FirstChildElement( "ActorType" );
	// Loop through each type in the Actor
	while ( pActorType ) {

		// create a new Actor type.
		THROW_GAME_EXCEPTION_IF(!pActorType->Attribute("name"),"Error m_Name ActorType no definido ");
		std::string name( pActorType->Attribute( "name" ) );
		CActorType_ptr elActorType( new CActorType() );

		if ( elActorType->Load( pActorType ) == false ) return false;
		m_mActorManager[name] = elActorType;
		// move to the next element
		pActorType = pActorType->NextSiblingElement( "ActorType" );

	}

	return true;

}

bool CActorManager::ActorExist( const std::string& elActor ) const {

	return m_mActorManager.find( elActor ) != m_mActorManager.end();

}

const CActorType* CActorManager::GetActorType( const std::string& elActor ){

	THROW_GAME_EXCEPTION_IF(!ActorExist(elActor),"Error GetActorType elActor no definido ");
	return m_mActorManager[elActor].get();

}

