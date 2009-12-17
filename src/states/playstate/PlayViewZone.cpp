/*
 * PlayViewZone.cpp
 *
 *  Created on: 15/12/2009
 *      Author: uberiain
 */

#include "PlayViewZone.h"

#include <xmlgui.h>

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
	m_scroller( new Scroller( 	getModel()->getMap(),
								getModel()->getResolution(),
								getModel()->getTopPadding(),
								m_areaZone ) ),
	m_move( false ) {
}
void PlayViewZone::initialize() {

	m_controller = new PlayControllerZone( this );
	m_zone->addMouseListener( m_controller );

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

	m_scroller->moveView( 	x,
							y );

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
	if (0 > X)
	{
		adjX = 0;
	}
	else if (X > m_areaZone.x + m_areaZone.width - 1)
	{
		adjX = m_areaZone.x + m_areaZone.width - 1;
	} else
		adjX = X;
	if (0 > Y)
	{
		adjY = 0;
	}
	else if (Y > m_areaZone.y + m_areaZone.height - 1)
	{
		adjY = m_areaZone.y + m_areaZone.height - 1;
	} else
		adjY = Y;
	m_selectarea.width = std::abs( m_firstselect.GetX() - adjX );
	m_selectarea.height = std::abs( m_firstselect.GetY() - adjY );
	m_selectarea.x = std::min( 	m_firstselect.GetX(),
								adjX );
	m_selectarea.y = std::min( 	m_firstselect.GetY(),
								adjY );
}
void PlayViewZone::setReleasedMouse( 	const int& X,
										const int& Y ) {

	if ( m_selection ) {

		//
		// Y esta es el area con todos los elementos a seleccionar.
		//
		m_selectarea.width = std::abs( m_firstselect.GetX() - X );
		m_selectarea.height = std::abs( m_firstselect.GetY() - Y );
		m_selectarea.x = std::min( 	m_firstselect.GetX(),
									X );
		m_selectarea.y = std::min( 	m_firstselect.GetY(),
									Y );

		// Aqui pasamos al model el area a seleccionar creo yo.

		m_selection = false; // Quitamos la seleccion.

	} else {
		// Se ha liberado el mouse pero no teniamos seleccion activa.
		// Posiblemente venimos de mover la rueda del raton, que genera un
		// mouse released al final de su movimiento.
		getModel()->resetMouse();
	}

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
	std::vector < gcn::Point >& allPoints = m_scroller->getPointPaint(); // Obtener los puntos isometricos a dibujar.
	//
	// Dibujamos el Terrain.
	//
	std::for_each( 	allPoints.begin(),
					allPoints.end(),
					boost::bind(	&PlayViewZone::PaintAllTerrain,
									this,
									_1 ) );
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
	//
	// Dibujamos los Actores.
	//
	std::for_each( 	allPoints.begin(),
					allPoints.end(),
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
//
//-------------------------------------------------------------------------------
//
void PlayViewZone::PaintAllTerrain( const gcn::Point& pLocal ) {

	//
	// Obtener el tile que se ha de pintar en funcion del
	// punto isometrico calculado.
	//
	std::vector < CTerrainMapa* > terrainCell =
			getModel()->ObtainTerrainCell( pLocal );

	gcn::Point pScreen = m_scroller->LocalToScreen( pLocal.GetX(),
													pLocal.GetY() );

	std::for_each( 	terrainCell.begin(),
					terrainCell.end(),
					boost::bind(	&CTerrainMapa::Draw,
									_1,
									game.getGui().getGraphics(),
									pScreen.GetX(),
									pScreen.GetY() ) );

}
void PlayViewZone::PaintAllBuilding( const gcn::Point& pLocal ) {

	std::vector < CBuildingMapa* > buildingCell =
			getModel()->ObtainBuildingCell( pLocal );

	gcn::Point pScreen = m_scroller->LocalToScreen( pLocal.GetX(),
													pLocal.GetY() );
	std::for_each( 	buildingCell.begin(),
					buildingCell.end(),
					boost::bind(	&CBuildingMapa::Draw,
									_1,
									game.getGui().getGraphics(),
									pScreen.GetX(),
									pScreen.GetY() ) );

}
void PlayViewZone::PaintAllResource( const gcn::Point& pLocal ) {

	std::vector < CResourceMapa* > ResourceCell =
			getModel()->ObtainResourceCell( pLocal );

	gcn::Point pScreen = m_scroller->LocalToScreen( pLocal.GetX(),
													pLocal.GetY() );
	std::for_each( 	ResourceCell.begin(),
					ResourceCell.end(),
					boost::bind(	&CResourceMapa::Draw,
									_1,
									game.getGui().getGraphics(),
									pScreen.GetX(),
									pScreen.GetY() ) );

}
void PlayViewZone::PaintAllActor( const gcn::Point& pLocal ) {

	std::vector < CActorMapa* > ActorCell =
			getModel()->ObtainActorCell( pLocal );

	gcn::Point pScreen = m_scroller->LocalToScreen( pLocal.GetX(),
													pLocal.GetY() );
	std::for_each( 	ActorCell.begin(),
					ActorCell.end(),
					boost::bind(	&CActorMapa::Draw,
									_1,
									game.getGui().getGraphics(),
									pScreen.GetX(),
									pScreen.GetY() ) );
}
