/*
 * CBuildingManager.cpp
 *
 *  Created on: 28-oct-2008
 *      Author: 79481180
 */
#include "CBuildingManager.h"

#include <tinyxml.h>
#include <misc/utils.h>

#include "CBuildingType.h"

CBuildingManager::~CBuildingManager(){

	DeleteSTLMap(m_mBuildingManager);

}
bool CBuildingManager::Load(TiXmlElement* pXMLData) {
	if (!pXMLData)
		return false;

	TiXmlElement *pBuildingType = NULL;
	pBuildingType = pXMLData->FirstChildElement("BuildingType");

	// Loop through each type in the Buildings
	while (pBuildingType) {

		// create a new tile
		CBuildingType* elBuildingType = new CBuildingType();
		if (elBuildingType->Load(pBuildingType) == false)
			return false;
		// move to the next element
		m_mBuildingManager[elBuildingType->GetNameBuildingType()] = elBuildingType;
		pBuildingType = pBuildingType->NextSiblingElement("BuildingType");

	}

	return true;
}

CBuildingType* CBuildingManager::GetBuildingType(string elBuilding){

	return m_mBuildingManager[elBuilding];

}
