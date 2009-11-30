/*
 * CBuildingType.cpp
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */
#include "CBuildingType.h"

#include <tinyxml.h>
#include <guichan.hpp>

#include <game/GameException.h>

CBuildingType::~CBuildingType() {

	delete m_pImage;

}

bool CBuildingType::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	if ( pXMLData->Attribute( "AnchorX" ) ) {
		m_iAnchorX = atoi( pXMLData->Attribute( "AnchorX" ) );
	} else
		m_iAnchorX = 32;

	if ( pXMLData->Attribute( "AnchorY" ) ) {
		m_iAnchorY = atoi( pXMLData->Attribute( "AnchorY" ) );
	} else
		m_iAnchorY = 16;

	if ( pXMLData->Attribute( "space" ) ) {
		m_space = atoi( pXMLData->Attribute( "space" ) );
	} else
		m_space = 1;
	m_adjust = CPoint(	0,
						0 );
	/*
	 switch ( m_space ) {

	 case 4:
	 // Centro de los 4 tiles.
	 m_adjust.X() = -mouse->w() / 2;

	 break;

	 case 6:
	 //Centro de los 6 tiles.
	 // No hay desplazamiento.
	 break;

	 default:
	 break;

	 }
	 */
	THROW_GAME_EXCEPTION_IF( !pXMLData->Attribute( "image" ),"Error image BuildingType no definido");

	std::string s( pXMLData->Attribute( "image" ) );
	m_pImage = gcn::Image::load( s );
	/*

	 CRectangle rcSource(	0,	 0,	 p->GetWidth(),	 p->GetHeight() );
	 CPoint ptOffset( 	m_iAnchorX,	 m_iAnchorY );
	 m_pImage = new CImage( 	p,	 rcSource,	 ptOffset );
	 */

	return true;

}

void CBuildingType::Draw( 	gcn::Graphics* graphics,
							int destX,
							int destY ) {

	graphics->drawImage( 	m_pImage,
							destX - m_iAnchorX,
							destY - m_iAnchorY );

}

int CBuildingType::GetSpace() {

	return m_space;

}

