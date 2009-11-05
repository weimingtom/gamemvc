/*
 * CDir.cpp
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */
#include "CDir.h"

#include <tinyxml.h>

#include <sstream>
#include <game/GameException.h>

#include <misc/utils.h>

#include <SDL++/Point.h>
#include <SDL++/Canvas.h>
#include <SDL++/Image.h>
#include <SDL++/Rectangle.h>

CDir::~CDir() {

	for ( unsigned int i = 0; i < m_Image.size(); i++ ) {
		delete m_Image.at( i )->GetCanvas();
	}
	DeleteSTLContainer( m_Image );

}
bool CDir::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData )
		return false;

	THROW_GAME_EXCEPTION_IF(!(pXMLData->Attribute("name")),"Error m_Name Dir no definido");
	m_Name = pXMLData->Attribute( "name" );

	int r = 0;
	int g = 0;
	int b = 0;
	if ( pXMLData->Attribute( "r" ) )
		r = atoi( pXMLData->Attribute( "r" ) );
	if ( pXMLData->Attribute( "g" ) )
		g = atoi( pXMLData->Attribute( "g" ) );
	if ( pXMLData->Attribute( "b" ) )
		b = atoi( pXMLData->Attribute( "b" ) );

	TiXmlElement *pImage = NULL;
	pImage = pXMLData->FirstChildElement( "frame" );

	while ( pImage ) {

		// Añadir los diferentes frames a la direccion.
		int anchorX = 32;
		int anchorY = 16;

		if ( pImage->Attribute( "AnchorX" ) )
			anchorX = atoi( pImage->Attribute( "AnchorX" ) );

		if ( pImage->Attribute( "AnchorY" ) )
			anchorY = atoi( pImage->Attribute( "AnchorY" ) );

		string imagen = pImage->Attribute( "image" );
		CCanvas* p = CCanvas::LoadBMPCompatible( imagen );
		THROW_GAME_EXCEPTION_IF(!(p->GetSurface()),"Error carga imagen SDL_LoadBMP " + imagen + " no existe");
		CColor tmp( r, g, b );
		p->SetColorKey( tmp );
		CRectangle rcSource( 0, 0, p->GetWidth(), p->GetHeight() );
		CPoint ptOffset( anchorX, anchorY );
		m_Image.push_back( new CImage( p, rcSource, ptOffset ) );

		pImage = pImage->NextSiblingElement( "frame" );

	}

	return true;

}
int CDir::GetMaxImages() {
	return m_Image.size();
}
