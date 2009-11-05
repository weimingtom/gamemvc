/*
 * CStatus.cpp
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */
#include "CStatus.h"


#include <sstream>
#include "game/GameException.h"
#include <misc/utils.h>

#include "CDir.h"


CStatus::~CStatus(){

	DeleteSTLMap(m_mDir);

}

bool CStatus::Load(TiXmlElement* pXMLData) {

	if (!pXMLData)
		return false;

	THROW_GAME_EXCEPTION_IF(!(pXMLData->Attribute("name")),"Error name Actor no definido");
	m_Name = pXMLData->Attribute("name");
	THROW_GAME_EXCEPTION_IF(!(pXMLData->Attribute("frames")),"Error frames Actor no definido");
	m_iFrames = atoi(pXMLData->Attribute("frames"));

	TiXmlElement *pDir = NULL;
	pDir = pXMLData->FirstChildElement("dir");
	while (pDir) {

		CDir* laDir = new CDir();

		if (laDir->Load(pDir) == false)
			return false;

		// Añadir las diferentes direcciones al estado.
		m_mDir[laDir->GetName()] = laDir;
		pDir = pDir->NextSiblingElement("dir");

	}

	return true;
}
CDir* CStatus::GetDir(string laDir) {

	return m_mDir[laDir];

}
int CStatus::GetFrames(){
	return m_iFrames;
}
