/*
 * CTerrainMapaManager.h
 *
 *  Created on: 29-dic-2008
 *      Author: Administrador
 */

#ifndef CTERRAINMAPAMANAGER_H_
#define CTERRAINMAPAMANAGER_H_

#include <vector>
#include <boost/shared_ptr.hpp>

class PlayModel;
class TiXmlElement;
class CTerrainMapa;

class CTerrainMapaManager
{
public:

	CTerrainMapaManager( PlayModel* model );
	bool Load( TiXmlElement* pXMLData );

private:

	typedef boost::shared_ptr < CTerrainMapa > CTerrainMapa_ptr;

	PlayModel* m_pModel;
	std::vector < CTerrainMapa_ptr > m_TerrainMapa;

};

#endif /* CTERRAINMAPAMANAGER_H_ */
