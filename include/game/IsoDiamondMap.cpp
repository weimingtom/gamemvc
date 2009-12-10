/*
 * IsoDiamonMap.cpp
 *
 *  Created on: 09/12/2009
 *      Author: 79481180
 */

#include "IsoDiamondMap.h"

IsoDiamondMap::IsoDiamondMap( const MouseMap& mouseMap ) :
	Map( mouseMap ) {

}

IsoDiamondMap::~IsoDiamondMap() {

}

Vector2D IsoDiamondMap::MapToLocal( const Vector2D& p ) const {

	Vector2D local;
	local.x = p.x * mouseMap().w() + mouseMap().w() / 2;
	local.y = p.y * mouseMap().w() + mouseMap().w() / 2;

	return local;
}

Vector2D IsoDiamondMap::MapToLocal( int ix,
									int iy ) const {

	return MapToLocal( Vector2D( 	ix,
									iy ) );

}
gcn::Point IsoDiamondMap::MapToLocal( const gcn::Point& p ) const {

	gcn::Point local;
	local.X() = p.GetX() * mouseMap().w() + mouseMap().w() / 2;
	local.Y() = p.GetY() * mouseMap().w() + mouseMap().w() / 2;

	return local;
}
gcn::Point IsoDiamondMap::moveUnrestricted( Direction direction,
                                            const gcn::Point& fromPoint,
											int puntos ) const {
	int x = fromPoint.GetX();
	int y = fromPoint.GetY();

	switch ( direction ) {
		case NORTH: {
			x -= puntos;
			y -= puntos;
		}
		break;

		case NORTH_EAST: {
			y -= puntos;
		}
		break;

		case EAST: {
			x += puntos;
			y -= puntos;
		}
		break;

		case SOUTH_EAST: {
			x += puntos;
		}
		break;

		case SOUTH: {
			x += puntos;
			y += puntos;
		}
		break;

		case SOUTH_WEST: {
			y += puntos;
		}
		break;

		case WEST: {
			x -= puntos;
			y += puntos;
		}
		break;

		case NORTH_WEST: {
			x -= puntos;
		}
		break;

		default:
			// This should never be reached as all cases should have been
			// handled above.
			assert( true );
		break;
	}
	return gcn::Point( 	x,
						y );
}
