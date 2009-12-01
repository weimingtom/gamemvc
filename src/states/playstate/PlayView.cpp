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

	std::ostringstream ox, oy;
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

PlayView::PlayZoneView::PlayZoneView( PlayView& play ) :
	m_play( play ), m_move( false ) {
	//
	// Datos constantes del mapa
	// se sacan de la definicion del fichero
	// con el mapa, luego han de estar en el model.
	//
	const int iTile_W = mouse->w();
	const int iTile_H = mouse->h();
	//
	// Obtenemos el widget donde hemos de dibujar.
	m_zone = m_play.getXmlGui().getWidget( "zone" );
	//
	// Ya tenemos la zona donde dibujar,
	// hemos de calcular los parametros Isometricos
	// a utilizar.
	//
	m_areaZone = m_zone->getChildrenArea();

	m_iNumRows = m_play.getModel()->getResolution();
	m_iNumCols = m_play.getModel()->getResolution();
	m_iTile_HalfW = ( m_iTile_W = iTile_W ) / 2;
	m_iTile_HalfH = ( m_iTile_H = iTile_H ) / 2;
	m_TileRatio = m_iTile_W / float( m_iTile_H );
	m_hOffset = ( m_iNumCols - 1 ) * m_iTile_HalfW;
	m_vOffset = m_play.getModel()->getTopPadding();

	m_iWorldWidth = ( m_iNumRows + m_iNumCols ) * m_iTile_HalfW;
	m_iWorldHeight = ( m_iNumRows + m_iNumCols ) * m_iTile_HalfH + m_vOffset;

	m_MaxMapX = -( m_iWorldWidth - m_areaZone.width );
	m_MaxMapY = -( m_iWorldHeight - m_areaZone.height );
	//
	//  -- set the default view ot the middle of the overall map
	//
	m_MapX = m_MaxMapX / 2;
	m_MapY = m_MaxMapY / 2;

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
	getPointPaint(); // Obtener los puntos isometricos a dibujar.
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
CPoint PlayView::PlayZoneView::tileWalk( 	Direction direction,
											CPoint fromPoint,
											int puntos ) {

	int x = fromPoint.X();
	int y = fromPoint.Y();

	switch ( direction ) {
		case NORTH: {
			x -= puntos;
			y -= puntos;
		}
		break;

		case NORTH_EAST: {
			y -= puntos;
		}
		break;

		case EAST: {
			x += puntos;
			y -= puntos;
		}
		break;

		case SOUTH_EAST: {
			x += puntos;
		}
		break;

		case SOUTH: {
			x += puntos;
			y += puntos;
		}
		break;

		case SOUTH_WEST: {
			y += puntos;
		}
		break;

		case WEST: {
			x -= puntos;
			y += puntos;
		}
		break;

		case NORTH_WEST: {
			x -= puntos;
		}
		break;

		default:
			// This should never be reached as all cases should have been
			// handled above.
			assert( true );
		break;
	}
	return CPoint( 	x,
					y );
}
void PlayView::PlayZoneView::getPointPaint() {

	//
	// Calculamos los puntos isometricos dentro
	// del area ( World ) que hemos de dibujar.
	//
	//
	allPoints.clear();

	gcn::Rectangle area;

	area.x = -m_MapX - m_iWorldWidth / 2;
	area.y = -m_MapY - m_vOffset;
	area.width = m_areaZone.width - 1;
	area.height = m_areaZone.height - 1;
	//
	// Empecemos con los calculos del dibujo.
	//
	// Coordenadas de las esquinas.
	CPoint supIzq;
	CPoint supDch;
	CPoint infIzq;
	CPoint infDch;
	// Coordenanda de la rejilla.
	CPoint rejilla;
	//Variables para recorrer filas y casillas
	CPoint filaInicio;
	CPoint filaFin;
	CPoint filaActual;
	// Contador para filas pares impares.
	int contadorFilas = 0;
	//Centinelas
	bool terminado;
	bool terminadoFila;
	//
	// FASE 1 - Calculamos las coordenadas de las casillas en cada esquina
	//

	//Esquina superior izquierda:

	supIzq = calculaIso( 	area.x,
							area.y );

	//Esquina superior derecha:

	supDch = calculaIso( 	area.x + area.width,
							area.y );

	//Esquina inferior izquierda:

	infIzq = calculaIso( 	area.x,
							area.y + area.height );

	//Esquina inferior derecha:

	infDch = calculaIso( 	area.x + area.width,
							area.y + area.height );

	//
	// FASE 2 - Ampliamos el marco de dibujado
	//

	//Desplazamos cada esquina para alejarnos de la pantalla
	supIzq = tileWalk( 	NORTH_WEST,
						supIzq,
						1 );
	supDch = tileWalk( 	NORTH_EAST,
						supDch,
						1 );
	infIzq = tileWalk( 	SOUTH_WEST,
						infIzq,
						1 );
	infDch = tileWalk( 	SOUTH_EAST,
						infDch,
						1 );

	//Desplazamos las esquinas inferiores 2 pasos al sur para
	//compensar por los objetos altos
	infIzq = tileWalk( 	SOUTH,
						infIzq,
						2 );
	infDch = tileWalk( 	SOUTH,
						infDch,
						2 );

	//
	// FASE 3 - Bucle de dibujado
	//
	terminado = false;
	filaInicio = supIzq;
	filaFin = supDch;

	//Para cada fila
	while ( !terminado ) {
		terminadoFila = false;
		//Seleccionamos la primera casilla
		filaActual = filaInicio;
		//Para cada casilla
		while ( !terminadoFila ) {
			//Dibujamos la casilla
			// filaActual es el tile a pintar... ?.
			if ( validIso( filaActual ) )

			allPoints.push_back( filaActual );

			//Comprobamos si hemos llegado al final de la fila y si no,
			//nos movemos a la siguiente casilla
			if ( filaActual == filaFin )
				terminadoFila = true;
			else
				filaActual = tileWalk( 	EAST,
										filaActual,
										1 );
		}

		//Comprobamos si la fila recorrida era la ultima
		if ( ( filaInicio == infIzq ) && ( filaFin == infDch ) )
			terminado = true;
		else {
			//Si no lo era, movemos las casillas de inicio y fin
			//hacia abajo para comenzar con la siguiente
			if ( contadorFilas & 1 ) {
				//Fila impar
				filaInicio = tileWalk( 	SOUTH_WEST,
										filaInicio,
										1 );
				filaFin = tileWalk( SOUTH_EAST,
									filaFin,
									1 );
			} else {
				//Fila par
				filaInicio = tileWalk( 	SOUTH_EAST,
										filaInicio,
										1 );
				filaFin = tileWalk( SOUTH_WEST,
									filaFin,
									1 );
			}
			++contadorFilas;
		}
	}

}
bool PlayView::PlayZoneView::validIso( CPoint p ) {

	if ( ( p.X() < 0 ) || ( p.Y() < 0 ) || ( p.X() >= m_iNumRows ) || ( p.Y()
			>= m_iNumCols ) )
		return false;
	else
		return true;
}

CPoint PlayView::PlayZoneView::calculaIso( 	int wx,
											int wy ) {

	CPoint rejilla;
	CPoint p;

	rejilla = calcularRejilla( CPoint( 	wx,
										wy ) );
	p = tileWalk( 	EAST,
					CPoint( 0,
							0 ),
					rejilla.X() );
	p = tileWalk( 	SOUTH,
					p,
					rejilla.Y() );

	return p;
}
CPoint PlayView::PlayZoneView::calcularRejilla( CPoint punto ) {

	CPoint rejilla;
	CPoint indice;

	rejilla.X() = ( punto.X() + m_iTile_HalfW ) / m_iTile_W;
	rejilla.Y() = punto.Y() / m_iTile_H;
	indice.X() = ( punto.X() + m_iTile_HalfW ) % m_iTile_W;
	indice.Y() = punto.Y() % m_iTile_H;
	if ( indice.X() < 0 ) {
		indice.X() += m_iTile_W;
		--rejilla.X();
	}
	if ( indice.Y() < 0 ) {
		indice.Y() += m_iTile_H;
		--rejilla.Y();
	}

	switch ( mouse->computeLocation( indice ) ) {
		case MouseMap::CENTER:
			// No hacemos nada
		break;
		case MouseMap::NORTH_EAST:
			tileWalk( 	NORTH_EAST,
						rejilla );
		break;
		case MouseMap::NORTH_WEST:
			tileWalk( 	NORTH_WEST,
						rejilla );
		break;
		case MouseMap::SOUTH_EAST:
			tileWalk( 	SOUTH_EAST,
						rejilla );
		break;
		case MouseMap::SOUTH_WEST:
			tileWalk( 	SOUTH_WEST,
						rejilla );
		break;
		default:
			// This should never be reached as all cases should have been
			// handled above.
			assert( true );
		break;
	}

	return rejilla;

}
CPoint PlayView::PlayZoneView::WorldToScreen( 	int wx,
												int wy ) {

	return CPoint( 	wx + m_MapX,
					wy + m_MapY );

}
CPoint PlayView::PlayZoneView::WorldToScreen( CPoint p ) {

	return WorldToScreen( 	p.X(),
							p.Y() );

}
CPoint PlayView::PlayZoneView::LocalToWorld( 	int lX,
												int lY ) {

	CPoint pW;

	pW.X() = m_hOffset + m_iTile_HalfW - ( lY / 2 ) + ( lX / 2 );
	pW.Y() = m_vOffset + ( lY / 4 ) + ( lX / 4 );

	return pW;

}
CPoint PlayView::PlayZoneView::LocalToScreen( 	int lX,
												int lY ) {

	return WorldToScreen( LocalToWorld( lX,
										lY ) );

}

void PlayView::PlayZoneView::PaintAllTerrain( const CPoint& paintPoint ) {

	//	std::cout << "(" << paintPoint.GetX() << "," << paintPoint.GetY() << ")";

	//
	// Obtener el tile que se ha de pintar en funcion del
	// punto isometrico calculado.
	//
	CPoint pLocal = m_play.getModel()->IsoToLocal( paintPoint );

	std::vector < CTerrainMapa* > terrainCell =
			m_play.getModel()->ObtainTerrainCell( pLocal );

	CPoint pScreen = LocalToScreen( pLocal.GetX(),
									pLocal.GetY() );

	std::for_each( 	terrainCell.begin(),
					terrainCell.end(),
					boost::bind(	&CTerrainMapa::Draw,
									_1,
									game.getGui().getGraphics(),
									pScreen.GetX(),
									pScreen.GetY() ) );

}
void PlayView::PlayZoneView::PaintAllBuilding( const CPoint& paintPoint ) {

	CPoint pLocal = m_play.getModel()->IsoToLocal( paintPoint );

	std::vector < CBuildingMapa* > buildingCell =
			m_play.getModel()->ObtainBuildingCell( pLocal );

	CPoint pScreen = LocalToScreen( pLocal.GetX(),
									pLocal.GetY() );
	std::for_each( 	buildingCell.begin(),
					buildingCell.end(),
					boost::bind(	&CBuildingMapa::Draw,
									_1,
									game.getGui().getGraphics(),
									pScreen.GetX(),
									pScreen.GetY() ) );

}
void PlayView::PlayZoneView::moveView( 	int x,
										int y ) {

	// scroll the view by the specifed amounts
	m_MapX = m_MapX <= 0 ? std::max( 	m_MaxMapX,
										std::min(	0,
													m_MapX + x ) ) : m_MapX;
	m_MapY = m_MapY <= 0 ? std::max( 	m_MaxMapY,
										std::min(	0,
													m_MapY + y ) ) : m_MapY;

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
