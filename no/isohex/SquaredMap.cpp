/*
 * SquaredMap.cpp
 *
 *  Created on: 06/01/2010
 *      Author: uberiain
 */

#include "SquaredMap.hpp"

#include <cassert>

#include <guichan/point.hpp>

#include "IMouseMap.hpp"

SquaredMap::SquaredMap( const IMouseMap& mouseMap ) :
	Map( mouseMap ) {

}

SquaredMap::~SquaredMap() {

}

gcn::Point SquaredMap::plot( const gcn::Point& ptMap ) const {

	gcn::Point ptReturn;
	ptReturn.x = ptMap.x * mouseMap().w();
	ptReturn.y = ptMap.y * mouseMap().h();
	return ptReturn;

}
gcn::Point SquaredMap::move(	const gcn::Point& fromPoint,
								IMap::Direction screenDirection ) const {
	return moveUnrestricted( fromPoint, screenDirection );
}

gcn::Point SquaredMap::moveUnrestricted(	const gcn::Point& fromPoint,
											IMap::Direction direction ) const {
	int x = fromPoint.x;
	int y = fromPoint.y;

	switch ( direction ) {
		case NORTH: {
			--y;
		}
		break;

		case NORTH_EAST: {
			++x;
			--y;
		}
		break;

		case EAST: {
			++x;
		}
		break;

		case SOUTH_EAST: {
			++x;
			++y;
		}
		break;

		case SOUTH: {
			++y;
		}
		break;

		case SOUTH_WEST: {
			--x;
			++y;
		}
		break;

		case WEST: {
			--x;
		}
		break;

		case NORTH_WEST: {
			--x;
			--y;
		}
		break;

		default:
			// This should never be reached as all cases should have been
			// handled above.
			assert(true);
		break;
	}
	return gcn::Point( x, y );
}
Offset SquaredMap::scrollerOffset() const {

    return Offset(0,0,0,0);
}
