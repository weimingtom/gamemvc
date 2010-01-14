/*
 * CResourceMapa.cpp
 *
 *  Created on: 30-dic-2008
 *      Author: 79481180
 */

#include "CResourceMapa.h"

#include <tinyxml.h>
#include <guichan.hpp>

#include <game/GameException.h>

#include <game/BaseGameEntity.h>
#include <game/database/CResourceManager.h>
#include <game/database/CResourceType.h>

#include "CResourceMapaManager.h"
#include "PlayModel.h"

CResourceMapa::CResourceMapa( PlayModel* model ) :
	BaseGameEntity( BaseGameEntity::resource ), m_pModel( model ) {

}

bool CResourceMapa::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;
	gcn::Point p;
	THROW_GAME_EXCEPTION_IF(!pXMLData->Attribute("x"),"Error x ResourceMapa no definido")
	p.x = atoi( pXMLData->Attribute( "x" ) );

	THROW_GAME_EXCEPTION_IF(!pXMLData->Attribute("y"),"Error y ResourceMapa no definido")
	p.y = atoi( pXMLData->Attribute( "y" ) );

	std::string s( pXMLData->GetText() );
	m_pResourceType = ResourceManager.GetResourceType( s );
	/*
	 switch ( m_pResourceType->GetSpace() ) {

	 case 4:
	 m_pWorld->Free4Nodes( p );
	 break;

	 case 6:
	 m_pWorld->Free6Nodes( p );
	 break;

	 default:
	 m_pWorld->FreeNode( p );
	 break;

	 }
	 */
//	SetPos( m_pModel->getMap().MapToLocal( 	p.GetX(),
//											p.GetY() ) );
	m_pModel->GetCellMapa()->AddEntity( this );
	return true;
}
void CResourceMapa::Draw( 	gcn::Graphics* graphics,
							int destX,
							int destY ) const {

	m_pResourceType->Draw( 	graphics,
							destX,
							destY );

}

