/*
 * ActorManager.cpp
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */
#include "CActorManager.h"

#include <iostream>
#include <misc/utils.h>
#include <gameengine/CGameEngine.h>

#include "CActorType.h"

CActorManager::~CActorManager(){

	DeleteSTLMap(m_mActorManager);

}
bool CActorManager::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData )
		return false;

	TiXmlElement *pActorType = NULL;
	pActorType = pXMLData->FirstChildElement( "ActorType" );
	// Loop through each type in the Actor
	while ( pActorType ) {

		// create a new tile
		CActorType* elActorType = new CActorType();

		if ( elActorType->Load( pActorType ) == false )
			return false;

		// move to the next element
		m_mActorManager[elActorType->GetNameActorType()] = elActorType;
		pActorType = pActorType->NextSiblingElement( "ActorType" );

	}

	return true;

}

bool CActorManager::ActorExist( string elActor ) {

	return m_mActorManager.find( elActor ) != m_mActorManager.end();

}

CActorType* CActorManager::GetActorType( string elActor ) {

	return m_mActorManager[elActor];

}

