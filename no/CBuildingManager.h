/*
 * CBuildingManager.h
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */

#ifndef CBUILDINGMANAGER_H_
#define CBUILDINGMANAGER_H_

#include <string>
#include <map>
using namespace std;

#include <misc/Singleton.h>

class CBuildingType;
class TiXmlElement;

#define BuildingManager	Singleton<CBuildingManager>::GetSingletonPtr()

class CBuildingManager {
public:

	~CBuildingManager();
	CBuildingType*	GetBuildingType(string elBuilding);
	bool 			Load(TiXmlElement* pXMLData);

private:
	map<string , CBuildingType* > 	m_mBuildingManager;
};

#endif /* CBUILDINGMANAGER_H_ */
