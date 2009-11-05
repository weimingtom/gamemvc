/*
 * CTerrainType.h
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */

#ifndef CTERRAINTYPE_H_
#define CTERRAINTYPE_H_

#include <tinyxml.h>
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

#include "CTile.h"

class CTerrainType
{
public:

	bool Load( TiXmlElement* pXMLData );
	CTile* GetTile( int elTile ) {
		return m_vTileType.at( elTile ).get();
	}

	int GetNumTiles() const {
		return m_vTileType.size();
	}

private:

	typedef boost::shared_ptr < CTile > CTile_ptr;
	std::vector < CTile_ptr > m_vTileType; //! Vector tipos de tile por cada terreno.

};

#endif /* CTERRAINTYPE_H_ */
