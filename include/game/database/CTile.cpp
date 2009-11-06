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

	delete laLoseta.first;

}
bool CTile::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	if ( pXMLData->GetText() ) {

		string imagen = pXMLData->GetText();
		gcn::Image* image = gcn::Image::load( imagen );
		laLoseta.first = image;
		laLoseta.second.SetX( image->getWidth() / 2 );
		laLoseta.second.SetY( image->getHeight() / 2 - 1 );

	} else THROW_GAME_EXCEPTION_IF(1==1,"Error imagen Tile no definido");

	return true;
}
void CTile::Draw( 	gcn::Graphics* graphics,
					int destX,
					int destY ) {

	graphics->drawImage( 	laLoseta.first,
							destX - laLoseta.second.GetX(),
							destY - laLoseta.second.GetY() );

}
