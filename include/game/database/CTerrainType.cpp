/*
 * CTerrainType.cpp
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */
#include "CTerrainType.h"

bool CTerrainType::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	TiXmlElement *pTile = NULL;
	pTile = pXMLData->FirstChildElement( "tile" );
	// Loop through each type in the Terrain
	while ( pTile ) {

		// create a new tile
		CTile_ptr elTile( new CTile() );
		m_vTileType.push_back( elTile );
		if ( elTile->Load( pTile ) == false ) return false;
		// move to the next element
		pTile = pTile->NextSiblingElement( "tile" );

	}

	return true;

}
