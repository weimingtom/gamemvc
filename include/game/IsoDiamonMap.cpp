/*
 * IsoDiamonMap.cpp
 *
 *  Created on: 09/12/2009
 *      Author: 79481180
 */

#include "IsoDiamonMap.h"

IsoDiamonMap::IsoDiamonMap( const MouseMap& mouseMap ) :
	Map( mouseMap ) {

}

IsoDiamonMap::~IsoDiamonMap() {

}

Vector2D IsoDiamonMap::IsoToLocal( const Vector2D& p ) const {

	Vector2D local;
	local.x = p.x * mouseMap().w() + mouseMap().w() / 2;
	local.y = p.y * mouseMap().w() + mouseMap().w() / 2;

	return local;
}

Vector2D IsoDiamonMap::IsoToLocal( 	int ix,
									int iy ) const {

	return IsoToLocal( Vector2D( 	ix,
									iy ) );

}
gcn::Point IsoDiamonMap::IsoToLocal(const gcn::Point& p ) const{

	gcn::Point local;
	local.X() = p.GetX() * mouseMap().w() + mouseMap().w() / 2;
	local.Y() = p.GetY() * mouseMap().w() + mouseMap().w() / 2;

	return local;
}
