/*
 * PlayView.cpp
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#include "PlayView.h"

#include <functional>
#include <sstream>
#include <guichan.hpp>
#include <xmlgui.h>

#include <misc/debug.h>

#include <MyGame.h>

#include "PlayModel.h"
#include "PlayController.h"
#include "CTerrainMapa.h"
#include "CBuildingMapa.h"
#include "CResourceMapa.h"

PlayView::PlayView( PlayModel* model ) :
	View < PlayModel, PlayController > ( model ) {

	xmlgui.reset( new XmlGui() );
	xmlgui->parse( "./scripts/Play/gui.xml" );
	game.getGui().setTop( top = xmlgui->getWidget( "top" ) );

	top->requestFocus();

	m_ZoneView.reset( new PlayZoneView( *this ) );
	m_MsgLeftView.reset( new PlayMsgLeftView( *this ) );
	m_MsgCenterView.reset( new PlayMsgCenterView( *this ) );

}

PlayView::~PlayView() {

	game.getGui().setTop( NULL );

}

void PlayView::initialize() {

	m_controller = new PlayController( this );
	top->addKeyListener( m_controller );

	m_ZoneView->initialize();
	m_MsgLeftView->initialize();
	m_MsgCenterView->initialize();

}

void PlayView::draw() {

	game.getGui().draw();

	// --------------------------------------------------------------

	game.getGui().getGraphics()->_beginDraw();

	m_ZoneView->draw(); // Pintamos Zone.
	m_MsgLeftView->draw(); // Pintamos parte del msg left.
	m_MsgCenterView->draw(); // Pintamos parte del msg center.

	game.getGui().getGraphics()->_endDraw();

	// --------------------------------------------------------------

}

void PlayView::setMouse(	const std::string& text,
							const int &X,
							const int &Y ) {

	std::stringstream ox, oy;
	ox << X;
	oy << Y;
	m_MsgLeftView->setName( text );
	m_MsgLeftView->setPosX( ox.str() );
	m_MsgLeftView->setPosY( oy.str() );

}
void PlayView::resetMouse() {

	m_MsgLeftView->setName( "" );
	m_MsgLeftView->setPosX( "" );
	m_MsgLeftView->setPosY( "" );

}
XmlGui& PlayView::getXmlGui() const {
	return *xmlgui;
}
void PlayView::moveZone( 	int X,
							int Y ) {

	m_ZoneView->updateMoveView( X,
								Y );

}
void PlayView::resetMoveZone() {

	m_ZoneView->resetMove();

}
void PlayView::moveView( 	int X,
							int Y ) {

	m_ZoneView->moveView( 	X,
							Y );

}
//-------------------------------------------------------------------
//
// PlayZoneView
//

PlayView::PlayZoneView::PlayZoneView( const PlayView& play ) :
	m_play( play ),
	m_zone( m_play.getXmlGui().getWidget( "zone" ) ),
	m_areaZone(m_zone->getChildrenArea()),
	m_scroller( new Scroller( 	m_play.getModel()->getMap(),
	                        	m_play.getModel()->getResolution(),
	                        	m_play.getModel()->getTopPadding(),
	                            m_areaZone )),

	m_move( false ) {

}
void PlayView::PlayZoneView::initialize() {

	m_zone->addMouseListener( m_play.getController()->getZoneMouseListener() );

}
void PlayView::PlayZoneView::updateMoveView( 	int X,
												int Y ) {

	m_move = false;
	moveX = 0;
	moveY = 0;
	if ( X >= 0 && X <= 4 ) {

		m_move = true;
		moveX = 10;

	}
	if ( Y >= 0 && Y <= 4 ) {

		m_move = true;
		moveY = 10;

	}
	if ( X <= m_areaZone.width && X >= m_areaZone.width - 4 ) {

		m_move = true;
		moveX = -10;

	}
	if ( Y <= m_areaZone.height && Y >= m_areaZone.height - 4 ) {

		m_move = true;
		moveY = -10;

	}

}
void PlayView::PlayZoneView::resetMove() {

	m_move = false;
	moveX = 0;
	moveY = 0;

}
void PlayView::PlayZoneView::draw() {
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
	std::vector<gcn::Point>& allPoints=m_scroller->getPointPaint(); // Obtener los puntos isometricos a dibujar.
	//
	// Dibujamos el Terrain.
	//
	std::for_each( 	allPoints.begin(),
					allPoints.end(),
					boost::bind(	&PlayView::PlayZoneView::PaintAllTerrain,
									this,
									_1 ) );
	//
	// Dibujamos los Buildings.
	//
	std::for_each( 	allPoints.begin(),
					allPoints.end(),
					boost::bind(	&PlayView::PlayZoneView::PaintAllBuilding,
									this,
									_1 ) );
	//
	// Dibujamos los Resource.
	//
	std::for_each( 	allPoints.begin(),
					allPoints.end(),
					boost::bind(	&PlayView::PlayZoneView::PaintAllResource,
									this,
									_1 ) );

	/*
	 //
	 // Dibujamos los Actores.
	 //
	 for ( iter = allPoints.begin(); iter != allPoints.end(); iter++ ) {
	 PaintAllActor( ( *iter ) );
	 }
	 */
	game.getGui().getGraphics()->popClipArea();

}

void PlayView::PlayZoneView::PaintAllTerrain( const gcn::Point& paintPoint ) {

	//	std::cout << "(" << paintPoint.GetX() << "," << paintPoint.GetY() << ")";

	//
	// Obtener el tile que se ha de pintar en funcion del
	// punto isometrico calculado.
	//
	gcn::Point pLocal = m_play.getModel()->getMap().MapToLocal( paintPoint );

	std::vector < CTerrainMapa* > terrainCell =
			m_play.getModel()->ObtainTerrainCell( pLocal );

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
void PlayView::PlayZoneView::PaintAllBuilding( const gcn::Point& paintPoint ) {

	gcn::Point pLocal = m_play.getModel()->getMap().MapToLocal( paintPoint );

	std::vector < CBuildingMapa* > buildingCell =
			m_play.getModel()->ObtainBuildingCell( pLocal );

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
void PlayView::PlayZoneView::PaintAllResource( const gcn::Point& paintPoint ) {

	gcn::Point pLocal = m_play.getModel()->getMap().MapToLocal( paintPoint );

	std::vector < CResourceMapa* > ResourceCell =
			m_play.getModel()->ObtainResourceCell( pLocal );

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
void PlayView::PlayZoneView::moveView( 	int x,
										int y ) {

	m_scroller->moveView(x,y);

}
//-------------------------------------------------------------------
//
// PlayMsgLeftView
//
PlayView::PlayMsgLeftView::PlayMsgLeftView( PlayView& play ) :
	m_play( play ) {

	m_name
			= static_cast < gcn::TextField* > ( m_play.getXmlGui().getWidget( "name" ) );
	m_posX
			= static_cast < gcn::TextField* > ( m_play.getXmlGui().getWidget( "X" ) );
	m_posY
			= static_cast < gcn::TextField* > ( m_play.getXmlGui().getWidget( "Y" ) );

}
void PlayView::PlayMsgLeftView::initialize() {

}
void PlayView::PlayMsgLeftView::draw() {

}
void PlayView::PlayMsgLeftView::setName( const std::string& text ) {

	m_name->setText( text );

}
void PlayView::PlayMsgLeftView::setPosX( const std::string& x ) {

	m_posX->setText( x );

}
void PlayView::PlayMsgLeftView::setPosY( const std::string& y ) {

	m_posY->setText( y );

}
//-------------------------------------------------------------------
//
// PlayMsgCenterView
//
PlayView::PlayMsgCenterView::PlayMsgCenterView( PlayView& play ) :
	m_play( play ) {

	m_msgcenter = m_play.getXmlGui().getWidget( "msgcenter" );
}
void PlayView::PlayMsgCenterView::initialize() {

	m_msgcenter->addMouseListener( m_play.getController()->getMsgCenterMouseListener() );

}
void PlayView::PlayMsgCenterView::draw() {
	// Pintamos la parte del MsgCenter

	game.getGui().getGraphics()->pushClipArea( m_msgcenter->getDimension() );
	game.getGui().getGraphics()->setColor( gcn::Color( 0xffffff ) ); // The colour to be used when drawing. From here on, white will be used.
	game.getGui().getGraphics()->drawLine(	10,
											10,
											100,
											100 );
	game.getGui().getGraphics()->drawText(	"Otro texto de prueba",
											15,
											15 );
	game.getGui().getGraphics()->popClipArea();

}
