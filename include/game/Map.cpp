/*
 * Map.cpp
 *
 *  Created on: 09/12/2009
 *      Author: 79481180
 */

#include "Map.h"

Map::Map( const MouseMap& mouseMap ) :
	m_MouseMap_( mouseMap ) {

}

Map::~Map() {

}
const MouseMap& Map::mouseMap() const {

	return m_MouseMap_;
}
