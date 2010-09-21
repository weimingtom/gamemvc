/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#include "IsoSlideMap.hpp"

#include <cassert>

#include <guichan/point.hpp>

#include "IMouseMap.hpp"

IsoSlideMap::IsoSlideMap( const IMouseMap& mouseMap ) :
    Map( mouseMap ) {
}

/*virtual*/IsoSlideMap::~IsoSlideMap() {
}

/*virtual*/gcn::Point IsoSlideMap::plot( const gcn::Point& worldPoint ) const {
    int x = worldPoint.x * mouseMap().w() + worldPoint.y
            * mouseMap().w() / 2;

    int y = worldPoint.y * mouseMap().h() / 2;

    return gcn::Point( x,
                       y );
}

/*virtual*/gcn::Point IsoSlideMap::move( const gcn::Point& fromPoint,
                                                       Direction screenDirection ) const {
    return moveUnrestricted( fromPoint,
                             screenDirection );
}

/*virtual*/gcn::Point IsoSlideMap::moveUnrestricted( const gcn::Point& fromPoint,
                                                                   Direction screenDirection ) const {
    int x = fromPoint.x;
    int y = fromPoint.y;

    switch ( screenDirection ) {
        case NORTH: {
            ++x;
            y -= 2;
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
            ++y;
        }
            break;

        case SOUTH: {
            --x;
            y += 2;
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

/*virtual*/Offset IsoSlideMap::scrollerOffset() const {
    return Offset( 0,
                   0,
                   mouseMap().h() / 2,
                   mouseMap().h() / 2 );
}
