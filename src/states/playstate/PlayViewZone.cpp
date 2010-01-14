/*
 * PlayViewZone.cpp
 *
 *  Created on: 15/12/2009
 *      Author: uberiain
 */

#include "PlayViewZone.h"

#include <xmlgui.h>
#include <IsoHex/MapFactory.hpp>

#include <MyGame.h>

#include "PlayModel.h"
#include "PlayView.h"
#include "PlayControllerZone.h"

#include "CTerrainMapa.h"
#include "CBuildingMapa.h"
#include "CResourceMapa.h"
#include "CActorMapa.h"

PlayViewZone::PlayViewZone( PlayModel* model,
							XmlGui& xmlgui ) :
			View < PlayModel, PlayControllerZone > ( model ),
			m_zone( xmlgui.getWidget( "zone" ) ),
			m_areaZone( m_zone->getChildrenArea() ),
			ptMouseMap( new MouseMap( Model().getMouseMap() ) ),
			m_tileAnchor( gcn::Point( 	ptMouseMap->w() / 2,
										ptMouseMap->h() / 2 ) ),
			ptIsoMap( new MapFactory(	IMap::ISO_DIAMOND_MAP_TYPE,
						*ptMouseMap )),
			ptScroller( new Scroller( 	*ptIsoMap,
										gcn::Rectangle( 0,
														0,
														Model().getResolution(),
														Model().getResolution() ),
										m_areaZone,
										m_tileAnchor,
										Model().getTopPadding() ) ),
			m_move( false ) {

	ptScroller->Center( ptScroller->plot( gcn::Point(	0,
														0 ) ) );
	m_zone->setFocusable( true );
	m_zone->requestFocus();

}
PlayViewZone::~PlayViewZone() {

	ptScroller.reset();
	ptMouseMap.reset();

}

void PlayViewZone::initialize() {

	setController( new PlayControllerZone( this ));
	m_zone->addMouseListener( &Controller() );
	m_zone->addKeyListener( &Controller() );

}
void PlayViewZone::draw() {

	//
	// Vemos si el mouse esta en la zona de movimiento.
	//
	if ( m_move ) moveView( moveX,
							moveY );
	//
	// Dibujamos la parte del zone.
	//
	game.getGui().getGraphics()->pushClipArea( m_zone->getDimension() );
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
	 * un pelin de follón....
	 *
	 */
	//	std::vector < gcn::Point >& allPoints = m_scroller->getPointPaint(); // Obtener los puntos isometricos a dibujar.
	//
	// Dibujamos el Terrain.
	//
	std::for_each( 	ptScroller->begin(),
					ptScroller->end(),
					boost::bind(	&PlayViewZone::PaintAllTerrain,
									this,
									_1 ) );
	/*
	 //
	 // Dibujamos los Buildings.
	 //
	 std::for_each( 	allPoints.begin(),
	 allPoints.end(),
	 boost::bind(	&PlayViewZone::PaintAllBuilding,
	 this,
	 _1 ) );
	 //
	 // Dibujamos los Resource.
	 //
	 std::for_each( 	allPoints.begin(),
	 allPoints.end(),
	 boost::bind(	&PlayViewZone::PaintAllResource,
	 this,
	 _1 ) );
	 */
	//
	// Dibujamos los Actores.
	//
	std::for_each( 	ptScroller->begin(),
					ptScroller->end(),
					boost::bind(	&PlayViewZone::PaintAllActor,
									this,
									_1 ) );

	//
	// Si tenemos activada el area de seleccion es hora de pintarla.
	//
	if ( m_selection ) {

		game.getGui().getGraphics()->setColor( gcn::Color( 0xff0000 ) ); // The colour to be used when drawing. From here on, white will be used.
		game.getGui().getGraphics()->drawRectangle( m_selectarea );

	}
	game.getGui().getGraphics()->popClipArea();

}
void PlayViewZone::updateMoveView( 	int X,
									int Y ) {

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
void PlayViewZone::resetMove() {

	m_move = false;
	moveX = 0;
	moveY = 0;

}
void PlayViewZone::moveView( 	int x,
								int y ) {

	if ( x < 0 )
		Scroll( std::abs( x ),
				IMap::EAST );
	else if ( x > 0 ) Scroll( 	x,
								IMap::WEST );

	if ( y < 0 )
		Scroll( std::abs( y ),
				IMap::SOUTH );
	else if ( y > 0 ) Scroll( 	y,
								IMap::NORTH );

}
void PlayViewZone::setPressedMouse( const int& X,
									const int& Y ) {

	m_selection = true; // Comienzo de seleccion de area.
	m_firstselect = gcn::Point( X,
								Y );
	m_selectarea.x = X;
	m_selectarea.y = Y;
	m_selectarea.width = 0;
	m_selectarea.height = 0;

}
void PlayViewZone::setDraggedMouse( const int& X,
									const int& Y ) {

	assert(m_selection); // Se supone que siempre es true al entrar aqui.
	int adjX;
	int adjY;
	if ( 0 > X ) {
		adjX = 0;
	} else if ( X > m_areaZone.x + m_areaZone.width - 1 ) {
		adjX = m_areaZone.x + m_areaZone.width - 1;
	} else
		adjX = X;
	if ( 0 > Y ) {
		adjY = 0;
	} else if ( Y > m_areaZone.y + m_areaZone.height - 1 ) {
		adjY = m_areaZone.y + m_areaZone.height - 1;
	} else
		adjY = Y;
	m_selectarea.width = std::abs( m_firstselect.x - adjX );
	m_selectarea.height = std::abs( m_firstselect.y - adjY );
	m_selectarea.x = std::min( 	m_firstselect.x,
								adjX );
	m_selectarea.y = std::min( 	m_firstselect.y,
								adjY );
}
void PlayViewZone::setReleasedMouse( 	const int& X,
										const int& Y ) {

	if ( m_selection ) {

		//
		// Y esta es el area con todos los elementos a seleccionar.
		//
		m_selectarea.width = std::abs( m_firstselect.x - X );
		m_selectarea.height = std::abs( m_firstselect.y - Y );
		m_selectarea.x = std::min( 	m_firstselect.x,
									X );
		m_selectarea.y = std::min( 	m_firstselect.y,
									Y );
		//
		// Tenemos el area a seleccionar.
		// seleccionemos los actores.
		//
		Scroller::iterator it;
		for ( it = ptScroller->begin( m_selectarea ); it != ptScroller->end(); ++it ) {

			gcn::Point pScreen = ptScroller->plot( ( *it ) );

			if ( m_selectarea.isPointInRect( 	pScreen.x,
												pScreen.y ) ) {

				std::vector < CActorMapa* > actorCell =
						Model().ObtainActorCell( Model().Map().MapToLocal <
								gcn::Point > ( ( *it ) ) );
				std::for_each( 	actorCell.begin(),
								actorCell.end(),
								boost::bind(	&CActorMapa::PonSelect,
												_1 ) );
			}

		}

		m_selection = false; // Quitamos la seleccion.

	} else {
		// Se ha liberado el mouse pero no teniamos seleccion activa.
		// Posiblemente venimos de mover la rueda del raton, que genera un
		// mouse released al final de su movimiento.
		Model().resetMouse();
	}

}
void PlayViewZone::Scroll( 	int screenExtent,
							IMap::Direction screenDirection ) {

	ptScroller->Scroll( screenExtent,
						screenDirection );

}

//
//-------------------------------------------------------------------------------
//
void PlayViewZone::PaintAllTerrain( const gcn::Point& pMap ) {

	//
	// Obtener el tile que se ha de pintar en funcion del
	// punto del mapa.
	//

	std::vector < CTerrainMapa* > terrainCell =
			Model().ObtainTerrainCell( Model().Map().MapToLocal <
					gcn::Point > ( pMap ) );

	gcn::Point pScreen = ptScroller->plot( pMap );

	std::for_each( 	terrainCell.begin(),
					terrainCell.end(),
					boost::bind(	&CTerrainMapa::Draw,
									_1,
									game.getGui().getGraphics(),
									pScreen.x,
									pScreen.y ) );

}
void PlayViewZone::PaintAllBuilding( const gcn::Point& pLocal ) {

	/*
	 std::vector < CBuildingMapa* > buildingCell =
	 Model().ObtainBuildingCell( pLocal );

	 //	gcn::Point pScreen = m_scroller->LocalToScreen( pLocal.x,
	 //													pLocal.y );
	 std::for_each( 	buildingCell.begin(),
	 buildingCell.end(),
	 boost::bind(	&CBuildingMapa::Draw,
	 _1,
	 game.getGui().getGraphics(),
	 pScreen.x,
	 pScreen.y ) );
	 */
}
void PlayViewZone::PaintAllResource( const gcn::Point& pLocal ) {
	/*
	 std::vector < CResourceMapa* > ResourceCell =
	 Model().ObtainResourceCell( pLocal );

	 //	gcn::Point pScreen = m_scroller->LocalToScreen( pLocal.x,
	 //													pLocal.y );
	 std::for_each( 	ResourceCell.begin(),
	 ResourceCell.end(),
	 boost::bind(	&CResourceMapa::Draw,
	 _1,
	 game.getGui().getGraphics(),
	 pScreen.x,
	 pScreen.y ) );
	 */
}
void PlayViewZone::PaintAllActor( const gcn::Point& pMap ) {

	std::vector < CActorMapa* >
			ActorCell = Model().ObtainActorCell( Model().Map().MapToLocal <
					gcn::Point > ( pMap ) );

	std::vector < CActorMapa* >::iterator it;
	for ( it = ActorCell.begin(); it != ActorCell.end(); ++it ) {

		gcn::Point pScreen = ptScroller->plot( pMap ) - gcn::Point(0,m_tileAnchor.y);
		gcn::Point desp;
		desp.x = static_cast<int>((*it)->Pos().x) % 64; // Ojo Ojo Ojo
		desp.y = static_cast<int>((*it)->Pos().y) % 64;
		gcn::Point p( (desp.x-desp.y)/2,(desp.x+desp.y)/4);
		pScreen += p;
		( *it )->Draw( 	game.getGui().getGraphics(),
						pScreen.x ,
						pScreen.y );

	}
	/*
	 std::for_each( 	ActorCell.begin(),
	 ActorCell.end(),
	 boost::bind(	&CActorMapa::Draw,
	 _1,
	 game.getGui().getGraphics(),
	 pScreen.x,
	 pScreen.y ) );
	 */

}
