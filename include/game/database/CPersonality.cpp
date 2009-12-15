/*
 * CPersonality.cpp
 *
 *  Created on: 15-dic-2008
 *      Author: 79481180
 */

#include "CPersonality.h"
#include <tinyxml.h>

#include <game/GameException.h>

#include "CStatus.h"

bool CPersonality::Load( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	TiXmlElement *pStatus = NULL;
	pStatus = pXMLData->FirstChildElement( "status" );
	while ( pStatus ) {

		CStatus_ptr elStatus( new CStatus() );
		THROW_GAME_EXCEPTION_IF(!pStatus->Attribute("name"),"Error Name Personality no definido");
		std::string name( pStatus->Attribute( "name" ) );
		if ( elStatus->Load( pStatus ) == false ) return false;
		// Añadir a los estados del actor el nuevo estado.
		m_mStatus[name] = elStatus;
		pStatus = pStatus->NextSiblingElement( "status" );

	}
	return true;

}
bool CPersonality::StatusExist( const std::string& status ) const {
	return m_mStatus.find( status ) != m_mStatus.end();
}
CStatus* CPersonality::GetStatus( const std::string& status ) {

	THROW_GAME_EXCEPTION_IF(!StatusExist(status),"Error GetStatus status no definido ");
	return m_mStatus[status].get();

}
