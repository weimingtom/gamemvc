/*
 * CFrame.cpp
 *
 *  Created on: 11/12/2009
 *      Author: 79481180
 */

#include "CFrame.h"

#include <tinyxml.h>
#include <guichan.hpp>

#include <game/GameException.h>

bool CFrame::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	int anchorX;
	int anchorY;

	if ( pXMLData->Attribute( "AnchorX" ) ) {
		anchorX = atoi( pXMLData->Attribute( "AnchorX" ) );
	} else
		anchorX = 32;

	if ( pXMLData->Attribute( "AnchorY" ) ) {
		anchorY = atoi( pXMLData->Attribute( "AnchorY" ) );
	} else
		anchorY = 16;

	THROW_GAME_EXCEPTION_IF( !pXMLData->Attribute( "image" ),
			"Error image Dir no definido" );
	std::string s( pXMLData->Attribute( "image" ) );
	gcn::Image* image = gcn::Image::load( s );
	m_Frame.first.reset( image );
	m_Frame.second.SetX( anchorX );
	m_Frame.second.SetY( anchorY );

	return true;

}

void CFrame::Draw( 	gcn::Graphics* graphics,
					int destX,
					int destY ) {

	graphics->drawImage( 	m_Frame.first.get(),
							destX - m_Frame.second.GetX(),
							destY - m_Frame.second.GetY() );

}
