/*
 * PlayViewZone.cpp
 *
 *  Created on: 15/12/2009
 *      Author: uberiain
 */

#include "playviewzone.h"

#include <xmlgui.h>
#include <boost/bind.hpp>

#include <isohex/MapFactory.hpp>
#include <misc/Interface.h>

#include <mygame.h>
#include <2d/Wall2D.h>
#include <Graph/HandyGraphFunctions.h>

#include "playmodel.h"
#include "playview.h"
#include "playcontrollerzone.h"

#include "cterrainmapa.h"
#include "cbuildingmapa.h"
#include "cresourcemapa.h"

#include "Graphics/SDLgdi.h"

#include "lua/Raven_Scriptor.h"

PlayViewZone::PlayViewZone( PlayModel* model_p,
                            XmlGui& xmlgui ) :
    View < PlayModel, PlayControllerZone >( model_p ), m_interface_( model().interface() ), m_zone( xmlgui.getWidget( "zone" ) ), m_areaZone( m_zone->getChildrenArea() ), m_pos( m_zone->getClipRectangle() ), ptMouseMap( new MouseMap( model().getNameMouseMap() ) ), m_tileAnchor( gcn::Point( ptMouseMap->w()
                                                                                                                                                                                                                                                                                                       / 2,
                                                                                                                                                                                                                                                                                                   ptMouseMap->h()
                                                                                                                                                                                                                                                                                                       / 2 ) ), ptIsoMap( new MapFactory( IMap::ISO_DIAMOND_MAP_TYPE,
                                                                                                                                                                                                                                                                                                                                          *ptMouseMap ) ), ptScroller( new Scroller( *ptIsoMap,
                                                                                                                                                                                                                                                                                                                                                                                     gcn::Rectangle( 0,
                                                                                                                                                                                                                                                                                                                                                                                                     0,
                                                                                                                                                                                                                                                                                                                                                                                                     model().getResolution(),
                                                                                                                                                                                                                                                                                                                                                                                                     model().getResolution() ),
                                                                                                                                                                                                                                                                                                                                                                                     m_areaZone,
                                                                                                                                                                                                                                                                                                                                                                                     m_tileAnchor,
                                                                                                                                                                                                                                                                                                                                                                                     model().getTopPadding() ) ), m_move( false ), m_selection( false )
{

  ptScroller->center( ptScroller->plot( gcn::Point( 0,
                                                    0 ) ) );
  m_zone->setFocusable( true );
  m_zone->requestFocus();
  m_sdlgdi_ = new SDLgdi( m_interface_.screen().getGraphics(),
                          ptScroller,
                          model().Map() );
  model().Map().setScroller( ptScroller );

}
PlayViewZone::~PlayViewZone()
{

  ptScroller.reset();
  ptMouseMap.reset();
  delete m_sdlgdi_;

}

void PlayViewZone::Initialize()
{

  controller( new PlayControllerZone( this ) );
  m_zone->addMouseListener( &controller() );
  m_zone->addKeyListener( &controller() );

}
void PlayViewZone::Draw()
{

  //
  // Vemos si el mouse esta en la zona de movimiento.
  //
  if ( m_move ) moveView( moveX,
                          moveY );
  //
  // Dibujamos la parte del zone.
  //
  m_interface_.screen().getGraphics()->pushClipArea( m_pos );
  /*
   * Actualizar el campo isometrico.
   *
   * 1.- Calcular los tiles que hemos de dibujar.
   * 2.- Dibujar por orden:
   * 		Terreno
   * 		Buildings
   * 		Actores
   *
   * Empezamos a dibujar el Terrain, despues los buildings y despues los actores.
   * Ya veremos como planteamos el movimiento de los actores, cambios de tile,etc.
   * o bien para elementos como minas, etc.. la creacion y destruccion de los mismos,
   * un pelin de foll�n....
   *
   */
  //	std::vector < gcn::Point >& allPoints = m_scroller->getPointPaint(); // Obtener los puntos isometricos a dibujar.
  //
  // Dibujamos el Terrain.
  //
  std::for_each( ptScroller->begin(),
                 ptScroller->end(),
                 boost::bind( &PlayViewZone::PaintAllTerrain,
                              this,
                              _1 ) );

  //
  // Visualizar las ayudas de render.
  //
  this->Render();
  //
  // Visualizar resto de elementos.
  //
  std::for_each( ptScroller->begin(),
                 ptScroller->end(),
                 boost::bind( &PlayViewZone::PaintAll,
                              this,
                              _1 ) );
  /*
   //
   // Dibujamos los Buildings.
   //
   std::for_each(ptScroller->begin(), ptScroller->end(), boost::bind(
   &PlayViewZone::PaintAllBuilding, this, _1));

   //
   // Dibujamos los Resource.
   //
   std::for_each(ptScroller->begin(), ptScroller->end(), boost::bind(
   &PlayViewZone::PaintAllResource, this, _1));

   //
   // Dibujamos los Actores.
   //
   std::for_each(ptScroller->begin(), ptScroller->end(), boost::bind(
   &PlayViewZone::PaintAllActor, this, _1));
   */
  //
  // Si tenemos activada el area de seleccion es hora de pintarla.
  //
  if ( m_selection ) {

    m_interface_.screen().getGraphics()->setColor( gcn::Color::White ); // The colour to be used when drawing. From here on, white will be used.
    m_interface_.screen().getGraphics()->drawRectangle( m_selectarea );

  }
  m_interface_.screen().getGraphics()->popClipArea();

}
void PlayViewZone::Render()
{

  if ( script->GetBool( "ShowGraph" ) ) GraphHelper_DrawUsingGDI( model().GetNavGraph(),
                                                                  gcn::Color::Black );
  if ( script->GetBool( "ShowWalls" ) ) {
    //render any walls
    gdi->SetPenColor( gcn::Color::Cyan );
    for ( unsigned int w = 0; w < model().GetWalls().size(); ++w ) {
      model().GetWalls().at( w )->Render( true ); //true flag shows normals
    }
  }
}
void PlayViewZone::updateMoveView( int X,
                                   int Y )
{

  m_move = false;
  moveX = 0;
  moveY = 0;
  if ( X >= 0 && X <= 4 ) {

    m_move = true;
    moveX = 10;

  } else if ( X <= m_areaZone.width && X >= m_areaZone.width - 4 ) {

    m_move = true;
    moveX = -10;

  }
  if ( Y >= 0 && Y <= 4 ) {

    m_move = true;
    moveY = 10;

  } else if ( Y <= m_areaZone.height && Y >= m_areaZone.height - 4 ) {

    m_move = true;
    moveY = -10;

  }

}
void PlayViewZone::resetMove()
{

  m_move = false;
  moveX = 0;
  moveY = 0;

}
void PlayViewZone::moveView( int x,
                             int y )
{

  if ( x < 0 )
    Scroll( std::abs( x ),
            IMap::EAST );
  else if ( x > 0 ) Scroll( x,
                            IMap::WEST );

  if ( y < 0 )
    Scroll( std::abs( y ),
            IMap::SOUTH );
  else if ( y > 0 ) Scroll( y,
                            IMap::NORTH );

}

void PlayViewZone::paintSelectedArea( const gcn::Rectangle area )
{

  m_selectarea = area;
  m_selection = true;

}

void PlayViewZone::setSelectedArea( const gcn::Rectangle& area )
{

  //
  // Y esta es el area con todos los elementos a seleccionar.
  //
  m_selectarea = area;
  model().clearMultipleActors();
  if ( m_selectarea.width == 0 && m_selectarea.height == 0 ) {
    //
    // Solo tenemos un punto seleccionado, veamos el actor que contiene.
    //
    gcn::Point pScreen( m_selectarea.x,
                        m_selectarea.y );
    gcn::Point p = model().Map().ScreenToLocal( pScreen );
    if ( ( p.x >= 0 && p.x < model().cxClient() )
        && ( p.y >= 0 && p.y < model().cyClient() ) ) model().select1Actor( p );

  } else {
    //
    // Tenemos el area a seleccionar.
    // seleccionemos los actores.
    //
    Scroller::iterator it;
    for ( it = ptScroller->begin( m_selectarea ); it != ptScroller->end();
        ++it ) {

      gcn::Point pScreen = ptScroller->plot( ( *it ) );

      if ( m_selectarea.isPointInRect( pScreen.x,
                                       pScreen.y ) ) {

        model().selectMultipleActors( model().Map().MapToLocal < gcn::Point >( ( *it ) ) );

      }

    }
  }

  m_selection = false; // Quitamos la seleccion.

}
void PlayViewZone::setDestination( const gcn::Rectangle& area )
{

  if ( area.width == 0 && area.height == 0 ) {

    // Hemos de mandar a todos los seleccionados a un punto, juas.....
    model().moveToPosition( model().Map().ScreenToLocal( gcn::Point( area.x,
                                                                     area.y ) ) );

  }
  m_selection = false; // Quitamos la seleccion en caso de haberla....
}
const gcn::Rectangle& PlayViewZone::area() const
{

  return m_areaZone;

}
void PlayViewZone::Scroll( int screenExtent,
                           IMap::Direction screenDirection )
{

  ptScroller->scroll( screenExtent,
                      screenDirection );

}

//
//-------------------------------------------------------------------------------
//
void PlayViewZone::PaintAllTerrain( const gcn::Point& pMap )
{

  //
  // Obtener el tile que se ha de pintar en funcion del
  // punto del mapa.
  //

  std::vector < CTerrainMapa* > terrainCell =
      model().ObtainTerrainCell( model().Map().MapToLocal < gcn::Point >( pMap ) );

  gcn::Point pScreen = ptScroller->plot( pMap );

  std::for_each( terrainCell.begin(),
                 terrainCell.end(),
                 boost::bind( &CTerrainMapa::Draw,
                              _1,
                              m_interface_.screen().getGraphics(),
                              pScreen.x,
                              pScreen.y ) );

}
void PlayViewZone::PaintAllBuilding( const gcn::Point& pMap )
{

  std::vector < CBuildingMapa* > buildingCell =
      model().ObtainBuildingCell( model().Map().MapToLocal < gcn::Point >( pMap ) );
  gcn::Point pScreen = ptScroller->plot( pMap );

  std::for_each( buildingCell.begin(),
                 buildingCell.end(),
                 boost::bind( &CBuildingMapa::Draw,
                              _1,
                              m_interface_.screen().getGraphics(),
                              pScreen.x,
                              pScreen.y ) );

}
void PlayViewZone::PaintAllResource( const gcn::Point& pMap )
{

  std::vector < CResourceMapa* > ResourceCell =
      model().ObtainResourceCell( model().Map().MapToLocal < gcn::Point >( pMap ) );
  gcn::Point pScreen = ptScroller->plot( pMap );

  std::for_each( ResourceCell.begin(),
                 ResourceCell.end(),
                 boost::bind( &CResourceMapa::Draw,
                              _1,
                              m_interface_.screen().getGraphics(),
                              pScreen.x,
                              pScreen.y ) );

}
void PlayViewZone::PaintAllActor( const gcn::Point& pMap )
{

  std::vector < CActorMapa* > ActorCell =
      model().ObtainActorCell( model().Map().MapToLocal < gcn::Point >( pMap ) );

  std::vector < CActorMapa* >::iterator it;
  for ( it = ActorCell.begin(); it != ActorCell.end(); ++it ) {

    gcn::Point pScreen = model().Map().LocalToScreen( ( *it )->Pos() );
    ( *it )->Draw( m_interface_.screen().getGraphics(),
                   pScreen.x,
                   pScreen.y );

  }

}
void PlayViewZone::PaintAll( const gcn::Point& pMap )
{

  gcn::Point pLocal = model().Map().MapToLocal < gcn::Point >( pMap );
  CellMapa < BaseGameEntity* > cell =
      model().GetCellMapa()->GetCell( Vector2D( pLocal.x,
                                                pLocal.y ) );

  std::list < BaseGameEntity* >::iterator it;
  for ( it = cell.Members.begin(); it != cell.Members.end(); ++it ) {
    switch ( ( *it )->EntityType() )
    {

      case BaseGameEntity::building: {
        gcn::Point pScreen = ptScroller->plot( pMap );
        static_cast < CResourceMapa* >( *it )->Draw( m_interface_.screen().getGraphics(),
                                                     pScreen.x,
                                                     pScreen.y );
        break;
      }

      case BaseGameEntity::resource: {
        gcn::Point pScreen = ptScroller->plot( pMap );
        static_cast < CResourceMapa* >( *it )->Draw( m_interface_.screen().getGraphics(),
                                                     pScreen.x,
                                                     pScreen.y );
        break;
      }
      case BaseGameEntity::actor: {
        gcn::Point pScreen = model().Map().LocalToScreen( ( *it )->Pos() );
        static_cast < CActorMapa* >( *it )->Draw( m_interface_.screen().getGraphics(),
                                                  pScreen.x,
                                                  pScreen.y );
        break;
      }
      default:
        break;
    }

  }
}
