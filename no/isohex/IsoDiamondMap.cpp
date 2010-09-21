/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#include "IsoDiamondMap.hpp"

#include <cassert>

#include <guichan/point.hpp>

#include "IMouseMap.hpp"

IsoDiamondMap::IsoDiamondMap( const IMouseMap& mouseMap ) :
    Map( mouseMap ) {
}

/*virtual*/IsoDiamondMap::~IsoDiamondMap() {
}

/*virtual*/gcn::Point IsoDiamondMap::plot( const gcn::Point& worldPoint ) const {
    int x = ( worldPoint.x - worldPoint.y ) * mouseMap().w() / 2;
    int y = ( worldPoint.x + worldPoint.y ) * mouseMap().h() / 2;

    return gcn::Point( x,
                       y );
}

/*virtual*/gcn::Point IsoDiamondMap::move( const gcn::Point& fromPoint,
                                                         Direction direction ) const {
    return moveUnrestricted( fromPoint,
                             direction );
}

/*virtual*/gcn::Point IsoDiamondMap::moveUnrestricted( const gcn::Point& fromPoint,
                                                                     Direction direction ) const {
    int x = fromPoint.x;
    int y = fromPoint.y;

    switch ( direction ) {
        case NORTH: {
            --x;
            --y;
        }
            break;

        case NORTH_EAST: {
            --y;
        }
            break;

        case EAST: {
            ++x;
            --y;
        }
            break;

        case SOUTH_EAST: {
            ++x;
        }
            break;

        case SOUTH: {
            ++x;
            ++y;
        }
            break;

        case SOUTH_WEST: {
            ++y;
        }
            break;

        case WEST: {
            --x;
            ++y;
        }
            break;

        case NORTH_WEST: {
            --x;
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

/*virtual*/Offset IsoDiamondMap::scrollerOffset() const {
    return Offset( -mouseMap().w()/2,
                   -mouseMap().w()/2,
                   -mouseMap().h()/2,
                   -mouseMap().h()/2);
}
