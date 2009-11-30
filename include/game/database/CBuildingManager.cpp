/*
 * CBuildingManager.cpp
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */
#include "CBuildingManager.h"

#include <tinyxml.h>

#include <game/GameException.h>
#include <misc/utils.h>

#include "CBuildingType.h"

bool CBuildingManager::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	TiXmlElement *pBuildingType = NULL;
	pBuildingType = pXMLData->FirstChildElement( "BuildingType" );
	// Loop through each type in the Buildings
	while ( pBuildingType ) {

		// create a new Building type.
		THROW_GAME_EXCEPTION_IF(!pBuildingType->Attribute("name"),"Error m_Name BuildingType no definido ");
		std::string name = pBuildingType->Attribute( "name" );
		CBuildingType_ptr elBuildingType( new CBuildingType() );
		m_mBuildingManager[name] = elBuildingType;
		if ( elBuildingType->Load( pBuildingType ) == false ) return false;
		// move to the next element
		pBuildingType = pBuildingType->NextSiblingElement( "BuildingType" );

	}
	return true;

}
bool CBuildingManager::BuildingExist( const std::string elBuilding ) {
	return m_mBuildingManager.find( elBuilding ) != m_mBuildingManager.end();
}

CBuildingType* CBuildingManager::GetBuildingType( const std::string elBuilding ) {

	THROW_GAME_EXCEPTION_IF(!BuildingExist(elBuilding),"Error GetBuildingType elBuilding no definido ");
	return m_mBuildingManager[elBuilding].get();

}
