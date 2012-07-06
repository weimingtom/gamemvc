/*
 * IntroModel.cpp
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#include "intromodel.h"

#include <iostream>

#include <tinyxml.h>
#include <guichan/gui.hpp>

#include <misc/debug.h>
#include <misc/Log.h>

#include <game/database/CTerrainManager.h>
#include <game/database/CBuildingManager.h>
#include <game/database/CResourceManager.h>
#include <game/database/CActorManager.h>

#include <mygame.h>
#include <param.h>

IntroModel::IntroModel( MyGame& game )
: Model(),
game_( game ),
alpha_( 255 ),
final_( false ),
endtype_( IntroModel::CONTINUE ),
resolution_( game_.interface().actualResolution() ),
pt_( boost::bind( &IntroModel::Run,
        this ) ),
fi_( pt_.get_future() ),
thr_( boost::move( pt_ ) )
{

  boost::this_thread::yield(); // Pasamos el control al thread.
}

IntroModel::~IntroModel()
{

  thr_.interrupt(); // Si se ha terminado no se atiende....
  thr_.join();

}

void IntroModel::Update()
{

  alpha_--;
  if ( alpha_ < 0 ) {

    alpha_ = 0;
    final_ = true; // Marcamos finalizacion bucle video.

  }
  std::string msg;

  if ( fi_.get_state() == boost::future_state::waiting ) {

    // Continua el thread, seguimos esperando.
    msg += "Continua el thread .....";

  } else {

    int resultado = fi_.get();
    if ( resultado ) throw std::runtime_error( "Error carga inicial ficheros" );
    msg = "El thread ha terminado ...";
    if ( final_ ) {

      endtype( IntroModel::MENU );
      msg += " y tambien el video";

    } else {

      msg += " pero tenemos video ....";

    }

  }
  LDBG_( msg );
}
//-------------------------------------------------------------------------------
//
//  Set and Get de las variables de la clase
//
//-------------------------------------------------------------------------------
void IntroModel::endtype( const IntroModel::EndTypes& type )
{

  endtype_ = type;
}
IntroModel::EndTypes IntroModel::endtype() const
{

  return endtype_;

}

void IntroModel::final()
{

  final_ = true;

}
const int& IntroModel::alpha() const
{
  return alpha_;
}
const Interface::ScreenResolutionType& IntroModel::resolution() const
{
  return resolution_;
}
gcn::Gui& IntroModel::screen() const
{
return game_.interface().screen();
}
//-------------------------------------------------------------------------------
//
// Procedimientos privados
//
//-------------------------------------------------------------------------------
int IntroModel::Run()
{

  // Carga datos iniciales del GAME.
  int res = 0;
  try {

    TiXmlDocument doc( game_.param().gamedata );
    if ( doc.LoadFile() ) {

      if ( LoadXML( doc.FirstChildElement( "gamebase" ) ) ) {

        res = 0;

      } else {

        res = 1;
        BOOST_THROW_EXCEPTION( std::runtime_error("Error procesamiento XML") );
      }

    } else {

      res = 1;
      BOOST_THROW_EXCEPTION( std::runtime_error("Error carga fichero XML") );
    }
    return res;

  } catch ( boost::thread_interrupted const& ) {

    LDBG_( "Interrumpida la carga de XML" );
    return 2;
  }
  return 0;
}
bool IntroModel::LoadXML( TiXmlElement* pXMLData )
{

  if ( !pXMLData ) return false;

  if ( !TerrainManager.Load( pXMLData->FirstChildElement( "terrain" ) ) ) return false;

  if ( !BuildingManager.Load( pXMLData->FirstChildElement( "building" ) ) ) return false;

  if ( !ResourceManager.Load( pXMLData->FirstChildElement( "resource" ) ) ) return false;

  if ( !ActorManager.Load( pXMLData->FirstChildElement( "actor" ) ) ) return false;

  return true;
}
