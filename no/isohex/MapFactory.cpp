/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#include "MapFactory.hpp"

#include <cassert>

#include <guichan/point.hpp>

#include "IsoSlideMap.hpp"
#include "IsoStaggeredMap.hpp"
#include "IsoDiamondMap.hpp"
#include "HexSlideMap.hpp"
#include "HexStaggeredMap.hpp"
#include "HexDiamondMap.hpp"
#include "SquaredMap.hpp"

MapFactory::MapFactory( MapType mapType,
                        const IMouseMap& mouseMap ) {
    switch ( mapType ) {

        case SQUARED_MAP_TYPE:
            m_map_.reset( new SquaredMap( mouseMap ) );
            break;

        case ISO_SLIDE_MAP_TYPE:
            m_map_.reset( new IsoSlideMap( mouseMap ) );
            break;

        case ISO_STAGGERED_MAP_TYPE:
            m_map_.reset( new IsoStaggeredMap( mouseMap ) );
            break;

        case ISO_DIAMOND_MAP_TYPE:
            m_map_.reset( new IsoDiamondMap( mouseMap ) );
            break;

        case HEX_SLIDE_MAP_TYPE:
            m_map_.reset( new HexSlideMap( mouseMap ) );
            break;

        case HEX_STAGGERED_MAP_TYPE:
            m_map_.reset( new HexStaggeredMap( mouseMap ) );
            break;

        case HEX_DIAMOND_MAP_TYPE:
            m_map_.reset( new HexDiamondMap( mouseMap ) );
            break;

        default:
            // This should never be reached as all cases should have been
            // handled above.
            assert(true);
            break;

    }
}

MapFactory::~MapFactory() {
}

/*virtual*/gcn::Point MapFactory::plot( const gcn::Point& worldPoint ) const {
    return m_map_->plot( worldPoint );
}

/*virtual*/gcn::Point MapFactory::move( const gcn::Point& fromPoint,
                                        Direction screenDirection ) const {
    return m_map_->move( fromPoint,
                         screenDirection );
}

/*virtual*/gcn::Point MapFactory::moveUnrestricted( const gcn::Point& fromPoint,
                                                    Direction screenDirection ) const {
    return m_map_->moveUnrestricted( fromPoint,
                                     screenDirection );
}

/*virtual*/const IMouseMap&
MapFactory::mouseMap() const {
    return m_map_->mouseMap();
}

/*virtual*/Offset MapFactory::scrollerOffset() const {
    return m_map_->scrollerOffset();
}
