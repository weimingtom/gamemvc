/*
 * CTile.cpp
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */

#include "CTile.h"

#include <sstream>
#include <stdexcept>

#include <game/GameException.h>

#include <guichan.hpp>

CTile::~CTile() {

	delete m_laLoseta.first;

}
bool CTile::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	THROW_GAME_EXCEPTION_IF((!pXMLData->Attribute( "image" ) ),"Error imagen Tile no definido");
	std::string imagen( pXMLData->Attribute( "image" ) );
	gcn::Image* image = gcn::Image::load( imagen );
	m_laLoseta.first = image;
	m_laLoseta.second.SetX( image->getWidth() / 2 );
	m_laLoseta.second.SetY( image->getHeight() / 2 );

	return true;
}

void CTile::Draw( 	gcn::Graphics* graphics,
					int destX,
					int destY ) {

	graphics->drawImage( 	m_laLoseta.first,
							destX - m_laLoseta.second.GetX(),
							destY - m_laLoseta.second.GetY() );

}
