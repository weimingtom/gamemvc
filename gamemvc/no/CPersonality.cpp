/*
 * CPersonality.cpp
 *
 *  Created on: 15-dic-2008
 *      Author: 79481180
 */

#include "CPersonality.h"
#include <tinyxml.h>

#include <misc/utils.h>

#include "game/GameException.h"

#include "CStatus.h"

CPersonality::~CPersonality() {

	DeleteSTLMap(m_mStatus);

}

bool CPersonality::Load(TiXmlElement* pXMLData) {

	if (!pXMLData)
		return false;

	THROW_GAME_EXCEPTION_IF(!(pXMLData->Attribute("name")),"Error Name Personality no definido");
	m_Name = pXMLData->Attribute("name");

	TiXmlElement *pStatus = NULL;
	pStatus = pXMLData->FirstChildElement("status");
	while (pStatus) {

		CStatus* elStatus = new CStatus();

		if (elStatus->Load(pStatus) == false)
			return false;

		// Aadir a los estados del actor el nuevo estado.
		m_mStatus[elStatus->GetName()] = elStatus;
		pStatus = pStatus->NextSiblingElement("status");

	}
	return true;

}

string CPersonality::GetNamePersonality() {

	return m_Name;

}

CStatus* CPersonality::GetStatus(string status) {

	return m_mStatus[status];

}
