/*
 * Map.h
 *
 *  Created on: 09/12/2009
 *      Author: 79481180
 */

#ifndef MAP_H_
#define MAP_H_

#include <game/database/MouseMap.hpp>

class Map
{
public:

	Map(const MouseMap& mouseMap );
	virtual ~Map();
	const MouseMap& mouseMap() const;

private:

	const MouseMap& m_MouseMap_;

};

#endif /* MAP_H_ */
