/*
 * MapLocal.cpp
 *
 *  Created on: 12/01/2010
 *      Author: 79481180
 */

#include "MapLocal.h"

MapLocal::MapLocal( int size ) :
	m_LocalSize( size ) {

}

MapLocal::~MapLocal() {

}
gcn::Point MapLocal::LocalToScreen(const Vector2D& local, const gcn::Point& screen) const{

    gcn::Point desp;
    desp.x = static_cast<int>(local.x) % m_LocalSize;
    desp.y = static_cast<int>(local.y) % m_LocalSize;
    gcn::Point p( (desp.x-desp.y)/2,(desp.x+desp.y)/4);
    return screen + p;

}
