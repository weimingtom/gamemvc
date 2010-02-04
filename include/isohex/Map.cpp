/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#include "Map.hpp"
#include "MouseMap.hpp"

Map::Map(const IMouseMap& mouseMap)
: m_mouseMap_(mouseMap)
{
}



Map::~Map()
{
}



const IMouseMap&
Map::mouseMap() const
{
	return m_mouseMap_;
}
