/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#include "MouseMap.hpp"

#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>

#include <misc/log.h>

MouseMap::MouseMap( const std::string fileName ) :
	m_surface_( gcn::Image::load( fileName ) ) {
	init();
}

MouseMap::~MouseMap() {

}

void MouseMap::init() {

	m_data_.resize( w() * h() );

	const int width = w();
	const int height = h();

	const gcn::Color colorNE(	0xFF,
								0x00,
								0x00,
								0xFF );
	const gcn::Color colorSE(	0xFF,
								0xFF,
								0x00,
								0xFF );
	const gcn::Color colorSW(	0x00,
								0xFF,
								0x00,
								0xFF );
	const gcn::Color colorNW(	0x00,
								0x00,
								0xFF,
								0xFF );
	const gcn::Color colorCE(	0x00,
								0x00,
								0x00,
								0xFF ); // center color


	//	colorNE = 0xFF0000;
	//	colorSE = 0xFFFF00;
	//	colorSW = 0x00FF00;
	//	colorNW = 0x0000FF;
	//	colorCE = 0x000000;

	gcn::Color cur;
	std::vector < Location >::iterator it = m_data_.begin();
	for ( int j = 0; j < height; ++j ) {
		for ( int i = 0; i < width; ++i ) {

			cur = m_surface_->getPixel( i,
										j );
			*it
					= ( cur == colorCE ) ? MouseMap::CENTER : ( cur == colorNE ) ? MouseMap::NORTH_EAST : ( cur
							== colorSE ) ? MouseMap::SOUTH_EAST : ( cur
							== colorSW ) ? MouseMap::SOUTH_WEST : ( cur
							== colorNW ) ? MouseMap::NORTH_WEST : MouseMap::INVALID;
			if ( *it == MouseMap::INVALID ) {
				throw std::runtime_error( "Invalid color in iso mouse map" );
			}

			++it;

		}
	}

	// Logs the parsed data for debug.
	it = m_data_.begin();
	for ( int j = 0; j < height; ++j ) {
		std::ostringstream s;
		s.clear();
		for ( int i = 0; i < width; ++i ) {
			s << *it; // L_ << *it;

			++it;
		}
		LAPP_ << s.str(); // "\n";
	}

}

MouseMap::Location MouseMap::computeLocation( const CPoint& fineScreenPosition ) const {
	return m_data_.at( fineScreenPosition.GetX() + fineScreenPosition.GetY()
			* w() );
}

int MouseMap::w() const {
	return m_surface_->getWidth();
}

int MouseMap::h() const {
	return m_surface_->getHeight();
}

