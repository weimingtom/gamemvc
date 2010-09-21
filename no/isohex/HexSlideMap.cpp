/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#include "HexSlideMap.hpp"
#include "IMouseMap.hpp"

#include <guichan/point.hpp>

HexSlideMap::HexSlideMap( const IMouseMap& mouseMap ) :
    IsoSlideMap( mouseMap ) {
}

HexSlideMap::~HexSlideMap() {
}

gcn::Point HexSlideMap::move( const gcn::Point& fromPoint,
                                         Direction screenDirection ) const {
    if ( screenDirection == NORTH || screenDirection == SOUTH ) return fromPoint;
    return moveUnrestricted( fromPoint,
                             screenDirection );
}

Offset HexSlideMap::scrollerOffset() const {

    return Offset( 0,
                   0,
                   -mouseMap().h() / 4,
                   -mouseMap().h() / 4 * 3 );
}
