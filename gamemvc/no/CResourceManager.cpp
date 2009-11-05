/*
 * CResourceManager.cpp
 *
 *  Created on: 30-dic-2008
 *      Author: 79481180
 */

#include "CResourceManager.h"

#include <tinyxml.h>
#include <misc/utils.h>

#include "CResourceType.h"

CResourceManager::~CResourceManager(){

	DeleteSTLMap(m_mResourceManager);

}
bool CResourceManager::Load(TiXmlElement* pXMLData) {
	if (!pXMLData)
		return false;

	TiXmlElement *pResourceType = NULL;
	pResourceType = pXMLData->FirstChildElement("ResourceType");

	// Loop through each type in the Resources
	while (pResourceType) {

		// create a new tile
		CResourceType* elResourceType = new CResourceType();
		if (elResourceType->Load(pResourceType) == false)
			return false;
		// move to the next element
		m_mResourceManager[elResourceType->GetNameResourceType()] = elResourceType;
		pResourceType = pResourceType->NextSiblingElement("ResourceType");

	}

	return true;
}

CResourceType* CResourceManager::GetResourceType(string elResource){

	return m_mResourceManager[elResource];

}
