/*
 * loadInitData.cpp
 *
 *  Created on: 18-jun-2009
 *      Author: 79481180
 */

#include "loadInitData.h"

#include <iostream>
#include <boost/exception_ptr.hpp>
#include <boost/random.hpp>
#include <guichan.hpp>
#include <IsoHex/SDLException.hpp>

#include <misc/CrtlThread.h>
#include <CParam.h>
#include <game/GameException.h>

#include <game/database/CTerrainManager.h>
#include <game/database/CBuildingManager.h>
#include <game/database/CResourceManager.h>
#include <game/database/CActorManager.h>

//----------------------------------------------------------------------------

loadInitData::loadInitData( CrtlThread& control ) :
	m_control( control ) {

}

loadInitData::~loadInitData() {

}
void loadInitData::operator()() {

	// Carga datos iniciales del GAME.
	int res = 0;
	try {

		TiXmlDocument doc( param.gamedata );
		if ( doc.LoadFile() ) {

			LoadXML( doc.FirstChildElement( "gamebase" ) );

		} else {

			// TODO Que pasa si da error el fichero de carga inicial??.
			res = 1;
		}

	} catch ( boost::thread_interrupted const& ) {

		std::cout << "Interrumpida la carga de XML" << std::endl;

	} catch ( gcn::Exception const &e ) {

		std::cerr << e.getMessage() << std::endl;
		m_control.setError( 1 );

	} catch ( std::exception const &e ) {

		std::cerr << "trapped exception: " << e.what() << std::endl;
		m_control.setError( 1 );

	} catch ( ... ) {

		std::cerr << "Error en thread : -------- " << std::endl;
		m_control.setError( 1 );

	}
	m_control.stop();

}

bool loadInitData::LoadXML( TiXmlElement* pXMLData ) {

	if ( !pXMLData ) return false;

	if ( !TerrainManager.Load( pXMLData->FirstChildElement( "terrain" ) ) ) return false;

	if ( !BuildingManager.Load( pXMLData->FirstChildElement( "building" ) ) ) return false;

	if ( !ResourceManager.Load( pXMLData->FirstChildElement( "resource" ) ) ) return false;

	if ( !ActorManager.Load( pXMLData->FirstChildElement( "actor" ) ) ) return false;

	return true;
}
