/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#include "Scroller.hpp"

#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "IMouseMap.hpp"

Scroller::Scroller( const IMap& map,
                    const gcn::Rectangle& mapSize,
                    const gcn::Rectangle& outputRectangle,
                    const gcn::Point& tileAnchor,
                    const int& iPadding) :
    m_map_( map ),
    m_mouseMap_( map.mouseMap() ),
    m_mapSize_( mapSize ),
    m_outputRectangle_( outputRectangle ),
    m_outputOffset_( outputRectangle.x,
                     outputRectangle.y ),
    m_tileAnchor_( tileAnchor ) {

    int width = m_mapSize_.width;
    int height = m_mapSize_.height;

    const gcn::Rectangle r0( 0,
                             0,
                             m_mouseMap_.w(),
                             m_mouseMap_.h() );

    // set the map corners
    gcn::Rectangle r1( r0 );
    gcn::Rectangle r2( r0 );
    gcn::Rectangle r3( r0 );
    gcn::Rectangle r4( r0 );

    r1.Offset( m_map_.plot( gcn::Point( 0,
                                        0 ) ) );
    r2.Offset( m_map_.plot( gcn::Point( width - 1,
                                        0 ) ) );
    r3.Offset( m_map_.plot( gcn::Point( width - 1,
                                        height - 1 ) ) );
    r4.Offset( m_map_.plot( gcn::Point( 0,
                                        height - 1 ) ) );

    // compute the anchor rect
    m_anchorRectangle_.Copy( r1 ).Union( r2 ).Union( r3 ).Union( r4 );
    // Ajustamos el Padding para aquellos
    // elementos superiores al tamaño del tile.

    m_anchorRectangle_.y -= iPadding;
    m_anchorRectangle_.height += iPadding;

    // adjust the anchor rect
    if ( m_outputRectangle_.width > m_anchorRectangle_.width ) {
        m_anchorRectangle_.width = 0;
    } else {
        m_anchorRectangle_.width -= m_outputRectangle_.width;
    }

    if ( m_outputRectangle_.height > m_anchorRectangle_.height ) {
        m_anchorRectangle_.height = 0;
    } else {
        m_anchorRectangle_.height -= m_outputRectangle_.height;
    }

    // reduce anchor space to take into account the offset
    // specified by the map, offset needed to reduce jaginess
    // on the perimeter of the map.
    Offset offset = m_map_.scrollerOffset();

    m_anchorRectangle_.x += offset.m_left - m_tileAnchor_.x;
    m_anchorRectangle_.y += offset.m_top - m_tileAnchor_.y;
    m_anchorRectangle_.width -= ( offset.m_left + offset.m_right );
    m_anchorRectangle_.height -= ( offset.m_top + offset.m_bottom );
}

/* virtual */Scroller::~Scroller() {
}

void Scroller::scroll( int screenExtent,
                       IMap::Direction screenDirection ) {
    switch ( screenDirection ) {
        case IMap::NORTH: {
            m_anchor_.y = std::max( m_anchor_.y - screenExtent,
                                    (int) m_anchorRectangle_.y );
        }
            break;

        case IMap::NORTH_EAST: {
            scroll( screenExtent,
                    IMap::NORTH );
            scroll( screenExtent,
                    IMap::EAST );
        }
            break;

        case IMap::EAST: {
            m_anchor_.x = std::min( m_anchor_.x + screenExtent,
                                    m_anchorRectangle_.x
                                            + m_anchorRectangle_.width );
        }
            break;

        case IMap::SOUTH_EAST: {
            scroll( screenExtent,
                    IMap::SOUTH );
            scroll( screenExtent,
                    IMap::EAST );
        }
            break;

        case IMap::SOUTH: {
            m_anchor_.y = std::min( m_anchor_.y + screenExtent,
                                    m_anchorRectangle_.y
                                            + m_anchorRectangle_.height );
        }
            break;

        case IMap::SOUTH_WEST: {
            scroll( screenExtent,
                    IMap::SOUTH );
            scroll( screenExtent,
                    IMap::WEST );
        }
            break;

        case IMap::WEST: {
            m_anchor_.x = std::max( m_anchor_.x - screenExtent,
                                    (int) m_anchorRectangle_.x );
        }
            break;

        case IMap::NORTH_WEST: {
            scroll( screenExtent,
                    IMap::NORTH );
            scroll( screenExtent,
                    IMap::WEST );
        }
            break;

        default:
            // Should never happen, as all valid values are already handled.
            assert(true);
            break;
    }
}

void Scroller::center( const gcn::Point& screenPoint ) {
    // convert the screen point to the scroller coordinate
    gcn::Point pt0 = screenPoint;
    pt0 -= m_outputOffset_;
    pt0 += m_anchor_;

    m_anchor_.x = std::min( std::max( pt0.x - m_outputRectangle_.width / 2,
                                      m_anchorRectangle_.x ),
                            m_anchorRectangle_.x + m_anchorRectangle_.width );

    m_anchor_.y = std::min( std::max( pt0.y - m_outputRectangle_.height / 2,
                                      m_anchorRectangle_.y ),
                            m_anchorRectangle_.y + m_anchorRectangle_.height );

}

gcn::Point Scroller::plot( const gcn::Point& worldPoint ) const {
    return m_map_.plot( worldPoint ) - m_anchor_ + m_outputOffset_;
}

gcn::Point Scroller::move( const gcn::Point& fromPoint,
                           IMap::Direction screenDirection ) const {
    return m_map_.move( fromPoint,
                        screenDirection );
}

gcn::Point Scroller::map( const gcn::Point& pt ) const {
    // pt is the mouse coordinate
    gcn::Point pt0 = pt;

    // 0. substract the viewport offset
    pt0 -= m_outputOffset_;

    // 1. convert screen coord to scroller coord
    pt0 += m_anchor_;

    // 2. substract world coordonate for map position (0,0)
    pt0 -= m_map_.plot( gcn::Point( 0,
                                    0 ) );
    pt0 += m_tileAnchor_;

    // 3. get the coarse and fine mouse coordinates
    gcn::Point ptc( pt0.x / m_mouseMap_.w(),
                    pt0.y / m_mouseMap_.h() );

    gcn::Point ptf( pt0.x % m_mouseMap_.w(),
                    pt0.y % m_mouseMap_.h() );

    if ( ptf.x < 0 ) {
        ptf.x += m_mouseMap_.w();
        --ptc.x;
    }

    if ( ptf.y < 0 ) {
        ptf.y += m_mouseMap_.h();
        --ptc.y;
    }

    // 4. coarse tile walk
    gcn::Point pt1( 0,
                    0 );

    while ( ptc.y < 0 ) {
        pt1 = m_map_.moveUnrestricted( pt1,
                                       IMap::NORTH );
        ++ptc.y;
    }

    while ( ptc.y > 0 ) {
        pt1 = m_map_.moveUnrestricted( pt1,
                                       IMap::SOUTH );
        --ptc.y;
    }

    while ( ptc.x < 0 ) {
        pt1 = m_map_.moveUnrestricted( pt1,
                                       IMap::WEST );
        ++ptc.x;
    }

    while ( ptc.x > 0 ) {
        pt1 = m_map_.moveUnrestricted( pt1,
                                       IMap::EAST );
        --ptc.x;
    }

    // 5. use the mousemap lookup table
    switch ( m_mouseMap_.computeLocation( ptf ) ) {
        case IMouseMap::CENTER:
            // no movement
            break;

        case IMouseMap::NORTH_EAST:
            pt1 = m_map_.moveUnrestricted( pt1,
                                           IMap::NORTH_EAST );
            break;

        case IMouseMap::SOUTH_EAST:
            pt1 = m_map_.moveUnrestricted( pt1,
                                           IMap::SOUTH_EAST );
            break;

        case IMouseMap::SOUTH_WEST:
            pt1 = m_map_.moveUnrestricted( pt1,
                                           IMap::SOUTH_WEST );
            break;

        case IMouseMap::NORTH_WEST:
            pt1 = m_map_.moveUnrestricted( pt1,
                                           IMap::NORTH_WEST );
            break;

        default:
            // Should never happen.
            assert(true);
            break;
    }

    return pt1;
}

Scroller::iterator Scroller::begin() const {
    return begin( m_outputRectangle_ );
}

Scroller::iterator Scroller::begin( const Offset& offset ) const {
    return begin( m_outputRectangle_,
                  offset );
}

Scroller::iterator Scroller::begin( const gcn::Rectangle& rectangle,
									const Offset& offset ) const {
	return begin( gcn::Rectangle( 	rectangle.x - offset.m_left,
									rectangle.y - offset.m_top,
									rectangle.width + offset.m_left
											+ offset.m_right,
									rectangle.height + offset.m_top
											+ offset.m_bottom ) );
}

Scroller::iterator Scroller::begin( const gcn::Rectangle& rectangle ) const {
	iterator it;
	it.m_scroller_ = this;

	computeCorners( it, rectangle );

	// NOTE: The next if is sufficient. The operator++ will not stop
	//       till the iterator is vizible (on map) or it is outside
	//       the region of interest (that is, it is past the end).
	//       Replacing it with an while can get you in infinite loops.
	if ( it.isOnMap() == false ) {
		++it;
	}

	return it;
}

Scroller::iterator Scroller::end() const {
    return iterator();
}

gcn::Point Scroller::computeCoarseCorner( const gcn::Point& cornerPoint ) const {
    gcn::Point pt0 = cornerPoint;

    // 0. substract the viewport offset
    pt0 -= m_outputOffset_;

    // 1. convert screen coord to scroller coord
    pt0 += m_anchor_;

    // 2. substract world coordonate for map position (0,0)
    pt0 -= m_map_.plot( gcn::Point( 0,
                                    0 ) );
    pt0 += m_tileAnchor_;

    // 3. get the coarse mouse coordinates
    gcn::Point ptc( pt0.x / m_mouseMap_.w(),
                    pt0.y / m_mouseMap_.h() );

    // 4. do a fine adjustment
    if ( pt0.x < 0 ) {
        --ptc.x;
    }

    if ( pt0.y < 0 ) {
        --ptc.y;
    }

    // 5. fast eastward walk
    gcn::Point ptm = m_map_.moveUnrestricted( gcn::Point( 0,
                                                          0 ),
                                              IMap::EAST );
    ptm *= ptc.x;
    pt0 = ptm;

    // 6. fast southward walk
    ptm = m_map_.moveUnrestricted( gcn::Point( 0,
                                               0 ),
                                   IMap::SOUTH );
    ptm *= ptc.y;
    pt0 += ptm;

    return pt0;
}

void Scroller::computeCorners( iterator& it,
                               const gcn::Rectangle& rectangle ) const {
    int rbx = rectangle.x + rectangle.width -1; // right-bottom x
    int rby = rectangle.y + rectangle.height -1; // right-bottom y

    gcn::Point pt;

    pt.set( rectangle.x,
            rectangle.y );
    pt = computeCoarseCorner( pt );
    pt = m_map_.moveUnrestricted( pt,
                                  IMap::NORTH_WEST );
    it.m_corners_[iterator::NW_CORNER] = pt;

    pt.set( rbx,
            rectangle.y );
    pt = computeCoarseCorner( pt );
    pt = m_map_.moveUnrestricted( pt,
                                  IMap::NORTH_EAST );
    it.m_corners_[iterator::NE_CORNER] = pt;

    pt.set( rbx,
            rby );
    pt = computeCoarseCorner( pt );
    pt = m_map_.moveUnrestricted( pt,
                                  IMap::SOUTH_EAST );
    it.m_corners_[iterator::SE_CORNER] = pt;

    pt.set( rectangle.x,
            rby );
    pt = computeCoarseCorner( pt );
    pt = m_map_.moveUnrestricted( pt,
                                  IMap::SOUTH_WEST );
    it.m_corners_[iterator::SW_CORNER] = pt;

    it.m_point_ = it.m_corners_[iterator::NW_CORNER];

    it.m_row_ = 0;
}

const gcn::Rectangle& Scroller::mapSize() const {
    return m_mapSize_;
}

const gcn::Point& Scroller::anchor() const {
    return m_anchor_;
}

const gcn::Rectangle& Scroller::outputRectangle() const {
    return m_outputRectangle_;
}

const gcn::Point& Scroller::tileAnchor() const {
    return m_tileAnchor_;
}

const IMouseMap& Scroller::mouseMap() const {
    return m_mouseMap_;
}

Scroller::iterator::iterator() :
    m_scroller_( 0 ), m_row_( -1 ) {
}

Scroller::iterator::iterator( const iterator& it ) :
    m_scroller_( it.m_scroller_ ), m_row_( it.m_row_ ), m_point_( it.m_point_ ) {
    copyCorners( it );
}

Scroller::iterator::~iterator() {
}

bool Scroller::iterator::operator !=( const iterator& it ) const {
    return ( ( m_scroller_ != it.m_scroller_ ) || ( m_row_ != it.m_row_ )
            || ( m_point_ != it.m_point_ ) );
}

bool Scroller::iterator::operator ==( const iterator& it ) const {
    return ( ( m_scroller_ == it.m_scroller_ ) && ( m_row_ == it.m_row_ )
            && ( m_point_ == it.m_point_ ) );
}

Scroller::iterator::iterator& Scroller::iterator::operator =( const iterator& it ) {
    m_scroller_ = it.m_scroller_;
    m_row_ = it.m_row_;
    m_point_ = it.m_point_;

    copyCorners( it );

    return *this;
}

Scroller::iterator& Scroller::iterator::operator++() {
    while ( isValid() ) {
        assert(m_scroller_ != 0);

        const IMap& map = m_scroller_->m_map_;

        if ( m_point_ != m_corners_[NE_CORNER] ) {
            m_point_ = map.moveUnrestricted( m_point_,
                                             IMap::EAST );
        } else {
            if ( m_corners_[NW_CORNER] == m_corners_[SW_CORNER] ) {
                *this = iterator();
                break;
                //
                // This test for SQUARED_MAP_TYPE ( Lost end .... )
                //
            } else if (m_corners_[NW_CORNER].x >= m_corners_[SW_CORNER].x && m_corners_[NW_CORNER].y >= m_corners_[SW_CORNER].y ){
                *this = iterator();
            	break;
            }

            bool odd = m_row_ & 1;
            ++m_row_;

            m_corners_[NW_CORNER]
                    = map.moveUnrestricted( m_corners_[NW_CORNER],
                                            odd ? IMap::SOUTH_EAST : IMap::SOUTH_WEST );

            m_corners_[NE_CORNER]
                    = map.moveUnrestricted( m_corners_[NE_CORNER],
                                            odd ? IMap::SOUTH_WEST : IMap::SOUTH_EAST );

            m_point_ = m_corners_[NW_CORNER];

        }

        if ( isOnMap() ) {
            break;
        }
    }

    return *this;
}

gcn::Point&
Scroller::iterator::operator*() {
    return m_point_;
}

gcn::Point*
Scroller::iterator::operator->() {
    return &m_point_;
}

bool Scroller::iterator::isOnMap() {
    return ( ( m_scroller_ != 0 )
            && ( m_scroller_->mapSize().hasPoint( m_point_ ) ) );
}

void Scroller::iterator::copyCorners( const iterator& i ) {
    for ( int j = 0; j < CORNER_NO; ++j ) {
        m_corners_[j] = i.m_corners_[j];
    }
}

bool Scroller::iterator::isValid() const {
    // All values for m_point_ might be valid, so we can't use that for checks.
    // However, we can use safely m_scroller_ and m_row_.
    return ( ( m_scroller_ != 0 ) && ( m_row_ != -1 ) );
}

std::string Scroller::iterator::toString() const {
    std::stringstream s;

    s << "Scroller::iterator(" << "scroller: " << m_scroller_ << ", point : "
            << m_point_ << ", row: " << m_row_ << ")";

    return s.str();
}

std::ostream&
operator <<( std::ostream& os,
             const Scroller::iterator& it ) {
    os << it.toString().c_str();
    return os;
}
