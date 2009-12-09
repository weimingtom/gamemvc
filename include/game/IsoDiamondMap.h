/*
 * IsoDiamonMap.h
 *
 *  Created on: 09/12/2009
 *      Author: 79481180
 */

#ifndef ISODIAMONDMAP_H_
#define ISODIAMONDMAP_H_
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

class IsoDiamondMap: public Map
{
public:

	IsoDiamondMap( const MouseMap& mouseMap );
	virtual ~IsoDiamondMap();

	Vector2D MapToLocal( const Vector2D& p ) const;
	Vector2D MapToLocal( 	int ix,
							int iy ) const;
	gcn::Point MapToLocal(const gcn::Point& p ) const;

private:

	IsoDiamondMap(); // Unimplemented.
	IsoDiamondMap& operator=(const IsoDiamondMap&); // Unimplemented.

};

#endif /* ISODIAMONDMAP_H_ */
