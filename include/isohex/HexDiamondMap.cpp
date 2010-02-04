/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#include "HexDiamondMap.hpp"

#include <guichan/point.hpp>

HexDiamondMap::HexDiamondMap( const IMouseMap& mouseMap ) :
    IsoDiamondMap( mouseMap ) {
}

HexDiamondMap::~HexDiamondMap() {
}

gcn::Point HexDiamondMap::move( const gcn::Point& fromPoint,
                                Direction screenDirection ) const {
    if ( screenDirection == NORTH || screenDirection == SOUTH ) return fromPoint;
    return moveUnrestricted( fromPoint,
                             screenDirection );
}
