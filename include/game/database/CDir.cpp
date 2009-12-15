/*
 * CDir.cpp
 *
 *  Created on: 13-ago-2008
 *      Author: 79481180
 */
#include "CDir.h"

#include <tinyxml.h>

#include "CFrame.h"

bool CDir::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	TiXmlElement* pXMLFrame = pXMLData->FirstChildElement( "frame" );
	while ( pXMLFrame ) {

		CFrame_ptr elFrame( new CFrame() );
		if ( elFrame->Load( pXMLFrame ) == false ) return false;
		m_Frame.push_back( elFrame );
		pXMLFrame = pXMLFrame->NextSiblingElement( "frame" );

	}

	return true;

}
const CFrame* CDir::GetFrame( const int& numImage ) {

	return m_Frame.at( numImage ).get();

}

int CDir::GetMaxFrames() const {

	return m_Frame.size();

}
