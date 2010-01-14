/*
 * MapLocal.h
 *
 *  Created on: 12/01/2010
 *      Author: 79481180
 */

#ifndef MAPLOCAL_H_
#define MAPLOCAL_H_

#include <2d/Vector2D.h>
#include <guichan/point.hpp>

class MapLocal
{
public:

	MapLocal( int size );
	virtual ~MapLocal();

	template < class T >
	T MapToLocal( const gcn::Point& pMap ) const {

		T pLocal;

		pLocal.x = pMap.x * m_LocalSize + m_LocalSize / 2;
		pLocal.y = pMap.y * m_LocalSize + m_LocalSize / 2;

		return pLocal;
	}
	int getSize() const {
		return m_LocalSize;
	}

private:

	int m_LocalSize;

	MapLocal();

};

#endif /* MAPLOCAL_H_ */
