/*
 * Map.h
 *
 *  Created on: 09/12/2009
 *      Author: 79481180
 */

#ifndef MAP_H_
#define MAP_H_

#include <game/database/MouseMap.hpp>

#include "Direction.h"

class Map
{
public:

	Map( const MouseMap& mouseMap );
	virtual ~Map();
	const MouseMap& mouseMap() const;
	virtual gcn::Point moveUnrestricted( 	Direction direction,
											const gcn::Point& fromPoint,
											int puntos = 1 ) const =0;

private:

	const MouseMap& m_MouseMap_;

};

#endif /* MAP_H_ */
