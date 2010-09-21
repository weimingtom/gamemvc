/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#include "IsoStaggeredMap.hpp"

#include <cassert>
#include <guichan/point.hpp>

#include "IMouseMap.hpp"

IsoStaggeredMap::IsoStaggeredMap( const IMouseMap& mouseMap ) :
    Map( mouseMap ) {
}

/*virtual*/IsoStaggeredMap::~IsoStaggeredMap() {
}

/*virtual*/gcn::Point IsoStaggeredMap::plot( const gcn::Point& worldPoint ) const {
    int x = worldPoint.x * mouseMap().w() + ( worldPoint.y
            & 1 ) * mouseMap().w() / 2;
    int y = worldPoint.y * mouseMap().h() / 2;

    return gcn::Point( x,
                       y );
}

/*virtual*/gcn::Point IsoStaggeredMap::move( const gcn::Point& fromPoint,
                                             Direction direction ) const {
    return moveUnrestricted( fromPoint,
                             direction );
}

/*virtual*/gcn::Point IsoStaggeredMap::moveUnrestricted( const gcn::Point& fromPoint,
                                                         Direction direction ) const {
    int x = fromPoint.x;
    int y = fromPoint.y;

    switch ( direction ) {
        case NORTH: {
            y -= 2;
        }
            break;

        case NORTH_EAST: {
            x += y & 1; // add 1 if on odd line!
            --y;
        }
            break;

        case EAST: {
            ++x;
        }
            break;

        case SOUTH_EAST: {
            x += y & 1; // add 1 if on odd line!
            ++y;
        }
            break;

        case SOUTH: {
            y += 2;
        }
            break;

        case SOUTH_WEST: {
            x += ( y & 1 ) - 1; // delete 1 if on even line!
            ++y;
        }
            break;

        case WEST: {
            --x;
        }
            break;

        case NORTH_WEST: {
            x += ( y & 1 ) - 1; // delete 1 if on even line!
            --y;
        }
            break;

        default:
            // This should never be reached as all cases should have been
            // handled above.
            assert(true);
            break;
    }

    return gcn::Point( x,
                       y );
}

/*virtual*/Offset IsoStaggeredMap::scrollerOffset() const {
    return Offset( 0 ,
                   0,
                   mouseMap().h() / 2,
                   mouseMap().h() / 2 );
}
