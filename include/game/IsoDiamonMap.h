/*
 * IsoDiamonMap.h
 *
 *  Created on: 09/12/2009
 *      Author: 79481180
 */

#ifndef ISODIAMONMAP_H_
#define ISODIAMONMAP_H_
/**
 *  @brief Isometric diamond map.
 *
 * When rendered on screen, diamond maps look like this:
 *
 * @code
 *           0,0
 *        0,1   1,0
 *     0,2   1,1   2,0
 *  0,3   1,2   2,1   3,0
 *     1,3   2,2   3,1
 *        2,3   3,2
 *           3,3
 * @endcode
 */
#include <2d/Vector2D.h>
#include <misc/Point.h>
#include "Map.h"

class IsoDiamonMap: public Map
{
public:

	IsoDiamonMap( const MouseMap& mouseMap );
	virtual ~IsoDiamonMap();

	Vector2D MapToLocal( const Vector2D& p ) const;
	Vector2D MapToLocal( 	int ix,
							int iy ) const;
	gcn::Point MapToLocal(const gcn::Point& p ) const;

};

#endif /* ISODIAMONMAP_H_ */
