/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#include "HexStaggeredMap.hpp"

#include <guichan/point.hpp>

#include "IMouseMap.hpp"

HexStaggeredMap::HexStaggeredMap( const IMouseMap& mouseMap ) :
    IsoStaggeredMap( mouseMap ) {
}

HexStaggeredMap::~HexStaggeredMap() {
}

gcn::Point HexStaggeredMap::move( const gcn::Point& fromPoint,
                                             Direction screenDirection ) const {
    if ( screenDirection == NORTH || screenDirection == SOUTH ) return fromPoint;
    return moveUnrestricted( fromPoint,
                             screenDirection );
}

Offset HexStaggeredMap::scrollerOffset() const {

    return Offset( 0,
                   0,
                   -mouseMap().h() / 4,
                   -mouseMap().h() / 4 * 3 );
}
