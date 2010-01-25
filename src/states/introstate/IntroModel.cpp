/*
 * IntroModel.cpp
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#include "IntroModel.h"

#include <iostream>

#include <tinyxml.h>
#include <guichan/gui.hpp>

#include <game/database/CTerrainManager.h>
#include <game/database/CBuildingManager.h>
#include <game/database/CResourceManager.h>
#include <game/database/CActorManager.h>

#include <MyGame.h>
#include <CParam.h>

IntroModel::IntroModel( MyGame& game ) :
    Model(),
    m_game_( game ),
    alpha( 255 ),
    m_final( false ),
    m_endtype( IntroModel::CONTINUE ),
    m_res_( m_game_.interface().actualResolution() ),
    pt( boost::bind( &IntroModel::run,
                     this) ),
    fi( pt.get_future()),
    thr( boost::move( pt )){

    boost::this_thread::yield();    // Pasamos el control al thread.
}

IntroModel::~IntroModel() {

	thr.interrupt(); // Si se ha terminado no se atiende....
	thr.join();

}

void IntroModel::Update() {

    alpha--;
    if ( alpha < 0 ) {

        alpha = 0;
        m_final = true; // Marcamos finalizacion bucle video.

    }
    std::string msg;

    if ( fi.get_state() == boost::future_state::waiting ) {

        // Continua el thread, seguimos esperando.
        msg += "Continua el thread .....";

    } else {

        int resultado = fi.get();
        if ( resultado ) throw std::runtime_error( "Error carga inicial ficheros" );
        msg = "El thread ha terminado ...";
        if ( m_final ) {

            this->setEnd( IntroModel::MENU );
            msg += " y tambien el video";

        } else {

            msg += " pero tenemos video ....";

        }

    }
    std::cout << msg << std::endl;
}

void IntroModel::setEnd( const IntroModel::EndTypes& type ) {

	m_endtype = type;
}
IntroModel::EndTypes IntroModel::getEnd() const {

	return m_endtype;

}

void IntroModel::setFinal() {

	m_final = true;

}
int IntroModel::getAlpha() {
	return alpha;
}
const Interface::ScreenResolutionType& IntroModel::getResolution() const{
	return m_res_;
}
gcn::Gui& IntroModel::Gui() const{
	return m_game_.interface().screen();
}
//-------------------------------------------------------------------------------
//
// Procedimientos privados
//
//-------------------------------------------------------------------------------
int IntroModel::run(){

    // Carga datos iniciales del GAME.
    int res = 0;
    try {

        TiXmlDocument doc( param.gamedata );
        if ( doc.LoadFile() ) {

            if (LoadXML( doc.FirstChildElement( "gamebase" ) )){

                res = 0;

            } else {

                res = 1;
                BOOST_THROW_EXCEPTION(std::runtime_error("Error procesamiento XML"));
            }

        } else {

            res = 1;
            BOOST_THROW_EXCEPTION(std::runtime_error("Error carga fichero XML"));
        }
        return res;

    } catch ( boost::thread_interrupted const& ) {

        std::cout << "Interrumpida la carga de XML" << std::endl;
        return 2;
    }

}
bool IntroModel::LoadXML( TiXmlElement* pXMLData ) {

    if ( !pXMLData ) return false;

    if ( !TerrainManager.Load( pXMLData->FirstChildElement( "terrain" ) ) ) return false;

    if ( !BuildingManager.Load( pXMLData->FirstChildElement( "building" ) ) ) return false;

    if ( !ResourceManager.Load( pXMLData->FirstChildElement( "resource" ) ) ) return false;

    if ( !ActorManager.Load( pXMLData->FirstChildElement( "actor" ) ) ) return false;

    return true;
}
