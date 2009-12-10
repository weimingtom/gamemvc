/*
 * Scroller.cpp
 *
 *  Created on: 09/12/2009
 *      Author: 79481180
 */

#include "Scroller.h"

#include <cassert>

Scroller::Scroller( const Map& map,
					const int& resolution,
					const int& toppadding,
					const gcn::Rectangle& areaZone ) :
	m_map_( map ), m_mouseMap_( map.mouseMap() ), m_Resolution_( resolution ),
			m_TopPadding_( toppadding ), m_areaZone_( areaZone ) {

	const int iTile_W = m_mouseMap_.w();
	const int iTile_H = m_mouseMap_.h();

	m_iNumRows = m_Resolution_;
	m_iNumCols = m_Resolution_;
	m_iTile_HalfW = ( m_iTile_W = iTile_W ) / 2;
	m_iTile_HalfH = ( m_iTile_H = iTile_H ) / 2;
	m_TileRatio = m_iTile_W / float( m_iTile_H );
	m_hOffset = ( m_iNumCols - 1 ) * m_iTile_HalfW;
	m_vOffset = m_TopPadding_;

	m_iWorldWidth = ( m_iNumRows + m_iNumCols ) * m_iTile_HalfW;
	m_iWorldHeight = ( m_iNumRows + m_iNumCols ) * m_iTile_HalfH + m_vOffset;

	m_MaxMapX = -( m_iWorldWidth - m_areaZone_.width );
	m_MaxMapY = -( m_iWorldHeight - m_areaZone_.height );
	//
	//  -- set the default view ot the middle of the overall map
	//
	m_MapX = m_MaxMapX / 2;
	m_MapY = m_MaxMapY / 2;

}

std::vector < gcn::Point >& Scroller::getPointPaint() {

	//
	// Calculamos los puntos isometricos dentro
	// del area ( World ) que hemos de dibujar.
	//
	//
	allPoints.clear();

	gcn::Rectangle area;

	area.x = -m_MapX - m_iWorldWidth / 2;
	area.y = -m_MapY - m_vOffset;
	area.width = m_areaZone_.width - 1;
	area.height = m_areaZone_.height - 1;
	//
	// Empecemos con los calculos del dibujo.
	//
	// Coordenadas de las esquinas.
	gcn::Point supIzq;
	gcn::Point supDch;
	gcn::Point infIzq;
	gcn::Point infDch;
	// Coordenanda de la rejilla.
	gcn::Point rejilla;
	//Variables para recorrer filas y casillas
	gcn::Point filaInicio;
	gcn::Point filaFin;
	gcn::Point filaActual;
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
	supIzq = m_map_.moveUnrestricted( 	NORTH_WEST,
										supIzq );
	supDch = m_map_.moveUnrestricted( 	NORTH_EAST,
										supDch );
	infIzq = m_map_.moveUnrestricted( 	SOUTH_WEST,
										infIzq );
	infDch = m_map_.moveUnrestricted( 	SOUTH_EAST,
										infDch );

	//Desplazamos las esquinas inferiores 2 pasos al sur para
	//compensar por los objetos altos
	infIzq = m_map_.moveUnrestricted( 	SOUTH,
										infIzq,
										1 ); // <---- Es 2
	infDch = m_map_.moveUnrestricted( 	SOUTH,
										infDch,
										1 ); // <---- Es 2

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

			allPoints.push_back( m_map_.MapToLocal( filaActual ) );

			//Comprobamos si hemos llegado al final de la fila y si no,
			//nos movemos a la siguiente casilla
			if ( filaActual == filaFin )
				terminadoFila = true;
			else
				filaActual = m_map_.moveUnrestricted( 	EAST,
														filaActual );
		}

		//Comprobamos si la fila recorrida era la ultima
		if ( ( filaInicio == infIzq ) && ( filaFin == infDch ) )
			terminado = true;
		else {
			//Si no lo era, movemos las casillas de inicio y fin
			//hacia abajo para comenzar con la siguiente
			if ( contadorFilas & 1 ) {
				//Fila impar
				filaInicio = m_map_.moveUnrestricted( 	SOUTH_WEST,
														filaInicio );
				filaFin = m_map_.moveUnrestricted( 	SOUTH_EAST,
													filaFin );
			} else {
				//Fila par
				filaInicio = m_map_.moveUnrestricted( 	SOUTH_EAST,
														filaInicio );
				filaFin = m_map_.moveUnrestricted( 	SOUTH_WEST,
													filaFin );
			}
			++contadorFilas;
		}
	}
	return allPoints;
}
bool Scroller::validIso( const gcn::Point& p ) {

	if ( ( p.GetX() < 0 ) || ( p.GetY() < 0 ) || ( p.GetX() >= m_iNumRows )
			|| ( p.GetY() >= m_iNumCols ) )
		return false;
	else
		return true;
}

gcn::Point Scroller::calculaIso( 	int wx,
									int wy ) {

	gcn::Point rejilla;
	gcn::Point p;

	rejilla = calcularRejilla( gcn::Point( 	wx,
											wy ) );
	p = m_map_.moveUnrestricted( 	EAST,
									gcn::Point( 0,
												0 ),
									rejilla.X() );
	p = m_map_.moveUnrestricted( 	SOUTH,
									p,
									rejilla.Y() );

	return p;
}
gcn::Point Scroller::calcularRejilla( const gcn::Point& punto ) {

	gcn::Point rejilla;
	gcn::Point indice;

	rejilla.X() = ( punto.GetX() + m_iTile_HalfW ) / m_iTile_W;
	rejilla.Y() = punto.GetY() / m_iTile_H;
	indice.X() = ( punto.GetX() + m_iTile_HalfW ) % m_iTile_W;
	indice.Y() = punto.GetY() % m_iTile_H;
	if ( indice.X() < 0 ) {
		indice.X() += m_iTile_W;
		--rejilla.X();
	}
	if ( indice.Y() < 0 ) {
		indice.Y() += m_iTile_H;
		--rejilla.Y();
	}

	switch ( m_mouseMap_.computeLocation( indice ) ) {
		case MouseMap::CENTER:
			// No hacemos nada
		break;
		case MouseMap::NORTH_EAST:
			m_map_.moveUnrestricted( 	NORTH_EAST,
										rejilla );
		break;
		case MouseMap::NORTH_WEST:
			m_map_.moveUnrestricted( 	NORTH_WEST,
										rejilla );
		break;
		case MouseMap::SOUTH_EAST:
			m_map_.moveUnrestricted( 	SOUTH_EAST,
										rejilla );
		break;
		case MouseMap::SOUTH_WEST:
			m_map_.moveUnrestricted( 	SOUTH_WEST,
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

gcn::Point Scroller::WorldToScreen( int wx,
									int wy ) {

	return gcn::Point( 	wx + m_MapX,
						wy + m_MapY );

}
gcn::Point Scroller::WorldToScreen( const gcn::Point& p ) {

	return WorldToScreen( 	p.GetX(),
							p.GetY() );

}
gcn::Point Scroller::LocalToWorld( 	int lX,
									int lY ) {

	gcn::Point pW;

	pW.X() = m_hOffset + m_iTile_HalfW - ( lY / 2 ) + ( lX / 2 );
	pW.Y() = m_vOffset + ( lY / 4 ) + ( lX / 4 );

	return pW;

}
gcn::Point Scroller::LocalToScreen( int lX,
									int lY ) {

	return WorldToScreen( LocalToWorld( lX,
										lY ) );

}
void Scroller::moveView( 	int x,
							int y ) {

	// scroll the view by the specifed amounts
	m_MapX = m_MapX <= 0 ? std::max( 	m_MaxMapX,
										std::min(	0,
													m_MapX + x ) ) : m_MapX;
	m_MapY = m_MapY <= 0 ? std::max( 	m_MaxMapY,
										std::min(	0,
													m_MapY + y ) ) : m_MapY;

}
Scroller::~Scroller() {
	// TODO Auto-generated destructor stub
}
