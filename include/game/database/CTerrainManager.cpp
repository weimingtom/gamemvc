/*
 * CTerrainManager.cpp
 *
 *  Created on: 12-ago-2008
 *      Author: Administrador
 */
#include "CTerrainManager.h"

#include <sstream>
#include <game/GameException.h>

#include "CTerrainType.h"

bool CTerrainManager::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	TiXmlElement *pTerrainType = NULL;
	pTerrainType = pXMLData->FirstChildElement( "TerrainType" );
	// Loop through each type in the Terrain
	while ( pTerrainType ) {

		THROW_GAME_EXCEPTION_IF(!pTerrainType->Attribute("name"),"Error m_Name TerrainType no definido ");
		std::string name( pTerrainType->Attribute( "name" ));
		CTerrainType_ptr terrainType( new CTerrainType() );
		m_mTerrainManager[name] = terrainType;
		if ( terrainType->Load( pTerrainType ) == false ) return false;
		// move to the next element
		pTerrainType = pTerrainType->NextSiblingElement( "TerrainType" );
	}
	return true;
}
bool CTerrainManager::TerrainExist( const std::string elTerreno ) {
	return m_mTerrainManager.find( elTerreno ) != m_mTerrainManager.end();
}
CTerrainType* CTerrainManager::GetTerrainType( const std::string elTerreno ) {
	THROW_GAME_EXCEPTION_IF(!TerrainExist(elTerreno),"Error GetTerrainType elTerreno no definido ");
	return  m_mTerrainManager[elTerreno].get();
}

