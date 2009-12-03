/*
 * CResourceManager.cpp
 *
 *  Created on: 30-dic-2008
 *      Author: 79481180
 */
#include "CResourceManager.h"

#include <tinyxml.h>

#include <game/GameException.h>
#include "CResourceType.h"

bool CResourceManager::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	TiXmlElement *pResourceType = NULL;
	pResourceType = pXMLData->FirstChildElement( "ResourceType" );

	// Loop through each type in the Resources
	while ( pResourceType ) {

		// create a new Building type.
		THROW_GAME_EXCEPTION_IF( !pResourceType->Attribute( "name" ),
				"Error m_Name ResourceType no definido " );
		std::string name( pResourceType->Attribute( "name" ) );
		CResourceType_ptr elResourceType( new CResourceType() );
		m_mResourceManager[name] = elResourceType;
		if ( elResourceType->Load( pResourceType ) == false ) return false;
		pResourceType = pResourceType->NextSiblingElement( "ResourceType" );

	}

	return true;
}
bool CResourceManager::ResourceExist( const std::string& elResource ) {
	return m_mResourceManager.find( elResource ) != m_mResourceManager.end();
}

CResourceType* CResourceManager::GetResourceType( const std::string& elResource ) {

	THROW_GAME_EXCEPTION_IF(!ResourceExist(elResource),"Error GetResourceType elResource no definido ");
	return m_mResourceManager[elResource].get();

}
