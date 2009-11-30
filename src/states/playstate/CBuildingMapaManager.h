/*
 * CBuildingMapaManager.h
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */

#ifndef CBUILDINGMAPAMANAGER_H_
#define CBUILDINGMAPAMANAGER_H_

#include <vector>
#include <boost/shared_ptr.hpp>

class TiXmlElement;
class CBuildingMapa;
class PlayModel;

class CBuildingMapaManager
{
public:

	typedef boost::shared_ptr < CBuildingMapa > CBuildingMapa_ptr;

	CBuildingMapaManager( PlayModel* model );

	bool Load( TiXmlElement* pXMLData );

private:

	PlayModel* m_pModel;

	std::vector < CBuildingMapa_ptr > m_BuildingMapa;

};

#endif /* CBUILDINGMAPAMANAGER_H_ */
