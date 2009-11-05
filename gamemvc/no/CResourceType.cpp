/*
 * CResourceType.cpp
 *
 *  Created on: 30-dic-2008
 *      Author: 79481180
 */

#include "CResourceType.h"

#include <tinyxml.h>

#include <game/GameException.h>

#include <SDL++/Image.h>
#include <SDL++/Canvas.h>

#include <gameengine/CMouseMapManager.h>

CResourceType::~CResourceType() {

	delete m_pImage->GetCanvas();
	delete m_pImage;

}
bool CResourceType::Load(TiXmlElement* pXMLData) {

	if (!pXMLData)
		return false;

	THROW_GAME_EXCEPTION_IF(!pXMLData->Attribute("name"),"Error m_Name ResourceType no definido");
	m_Name = pXMLData->Attribute("name");


	if (pXMLData->Attribute("AnchorX")) {
		m_iAnchorX = atoi(pXMLData->Attribute("AnchorX"));
	} else
		m_iAnchorX = 32;

	if (pXMLData->Attribute("AnchorY")) {
		m_iAnchorY = atoi(pXMLData->Attribute("AnchorY"));
	} else
		m_iAnchorY = 16;

	if (pXMLData->Attribute("space")) {
		m_space = atoi(pXMLData->Attribute("space"));
	} else
		m_space = 1;
	m_adjust = CPoint(0,0);
	switch (m_space){

	case 4:
		// Centro de los 4 tiles.
		m_adjust.X() = - mouse->w()/2;
		break;

	case 6:
		//Centro de los 6 tiles.
		// No hay desplazamiento.
		break;

	default:
		break;

	}

	int r = 0;
	int g = 0;
	int b = 0;
	if (pXMLData->Attribute("r"))
		r = atoi(pXMLData->Attribute("r"));

	if (pXMLData->Attribute("g"))
		g = atoi(pXMLData->Attribute("g"));

	if (pXMLData->Attribute("b"))
		b = atoi(pXMLData->Attribute("b"));

	if (pXMLData->Attribute("image")) {
		string s = pXMLData->Attribute("image");
		CCanvas* p = CCanvas::LoadBMPCompatible(s);
		THROW_GAME_EXCEPTION_IF(!(p->GetSurface()),
			"Error carga imagen SDL_LoadBMP " + s
					+ " no existe");
		CColor tmp(r,g,b);
		p->SetColorKey(tmp);
		CRectangle rcSource(0,0,p->GetWidth(),p->GetHeight());
		CPoint     ptOffset(m_iAnchorX,m_iAnchorY);
		m_pImage = new CImage(p,rcSource,ptOffset);

	} else
		THROW_GAME_EXCEPTION_IF( 1==1,"Error image ResourceType no definido");

	return true;
}
void CResourceType::Draw(CCanvas* pDestSurface, CPoint puntoDest) {

	m_pImage->Put(pDestSurface,puntoDest+m_adjust);

}

string CResourceType::GetNameResourceType() {

	return m_Name;
}
int CResourceType::GetSpace(){

	return m_space;

}

