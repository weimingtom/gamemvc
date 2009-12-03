/*
 * CBuildingMapa.cpp
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */
#include "CBuildingMapa.h"

#include <tinyxml.h>
#include <guichan.hpp>

#include <game/GameException.h>

#include <game/database/BaseGameEntity.h>
#include <game/database/CTile.h>

#include <game/database/CBuildingManager.h>
#include <game/database/CBuildingType.h>

#include "CBuildingMapaManager.h"
#include "PlayModel.h"

CBuildingMapa::CBuildingMapa( PlayModel* model ) :
	BaseGameEntity( BaseGameEntity::building ), m_pModel( model ) {

}

bool CBuildingMapa::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;
	gcn::Point p;
	THROW_GAME_EXCEPTION_IF(!pXMLData->Attribute("x"),"Error x BuildingMapa no definido")
	p.X() = atoi( pXMLData->Attribute( "x" ) );

	THROW_GAME_EXCEPTION_IF(!pXMLData->Attribute("y"),"Error y BuildingMapa no definido")
	p.Y() = atoi( pXMLData->Attribute( "y" ) );

	std::string s( pXMLData->GetText() );
	m_pBuildingType = BuildingManager.GetBuildingType( s );
	/*
	 switch ( m_pBuildingType->GetSpace() ) {

	 case 4:
	 m_pModel->Free4Nodes( p );
	 break;

	 case 6:
	 m_pModel->Free6Nodes( p );
	 break;

	 default:
	 m_pModel->FreeNode( p );
	 break;

	 }
	 */
	SetPos( m_pModel->IsoToLocal( 	p.GetX(),
									p.GetY() ) );
	m_pModel->GetCellPartition()->AddEntity( this );
	return true;
}
void CBuildingMapa::Draw( 	gcn::Graphics* graphics,
							int destX,
							int destY ) {

	m_pBuildingType->Draw( 	graphics,
							destX,
							destY );

}
