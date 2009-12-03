/*
 * CBuildingMapaManager.cpp
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */
#include "CBuildingMapaManager.h"

#include <tinyxml.h>

#include "PlayModel.h"
#include "CBuildingMapa.h"

CBuildingMapaManager::CBuildingMapaManager( PlayModel* model ) :
	m_pModel( model ) {

}

bool CBuildingMapaManager::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	TiXmlElement *pBuildingMapa = NULL;
	pBuildingMapa = pXMLData->FirstChildElement( "building" );
	// Loop through each type in the Actor

	while ( pBuildingMapa ) {

		CBuildingMapa_ptr elBuildingMapa(new CBuildingMapa( m_pModel ));

		if ( elBuildingMapa->Load( pBuildingMapa ) == false ) return false;

		m_BuildingMapa.push_back( elBuildingMapa );
		pBuildingMapa = pBuildingMapa->NextSiblingElement( "building" );

	}

	return true;

}
