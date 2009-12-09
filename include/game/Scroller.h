/*
 * Scroller.h
 *
 *  Created on: 09/12/2009
 *      Author: 79481180
 */

#ifndef SCROLLER_H_
#define SCROLLER_H_

#include <guichan.hpp>
#include <misc/Point.h>
#include "database/MouseMap.hpp"
#include "Map.h"
#include "Direction.h"

class Scroller
{
public:
	Scroller(	const Map& map,
				const int& resolution,
				const int& toppadding,
				const gcn::Rectangle& areaZone );
	virtual ~Scroller();

	std::vector < gcn::Point >& getPointPaint();

	gcn::Point WorldToScreen( 	int wx,
								int wy );
	gcn::Point WorldToScreen( const gcn::Point& p );
	gcn::Point LocalToWorld( 	int lX,
								int lY );
	gcn::Point LocalToScreen( 	int lX,
								int lY );

	void moveView( 	int x,
					int y );

private:
	//! Map object used.
	const Map& m_map_;

	const MouseMap& m_mouseMap_;

	//! Output rectangle.
	const int m_Resolution_;
	const int m_TopPadding_;

	const gcn::Rectangle m_areaZone_;

	int m_iNumRows; //! Numero de filas mapa isometrico.
	int m_iNumCols; //! Numero columnas mapa isometico.
	int m_iTile_W; //! Ancho del tile.
	int m_iTile_H; //! Alto del tile.
	int m_iTile_HalfW; //! Mitad tamaño ancho tile.
	int m_iTile_HalfH; //! Mitad tamaño alto tile.
	double m_TileRatio; //! Proporcion tamaño tile
	int m_hOffset; //! Desplazamiento horizontal en el World Space.
	int m_vOffset; //! Desplazamiento vertical en el World Space.
	int m_iWorldWidth; //! Ancho en pixel del World map.
	int m_iWorldHeight; //! Alto en pixel del World map.
	int m_MaxMapX; //! Maximo desplazamiento en X.
	int m_MaxMapY; //! Maximo desplazamiento en Y;
	int m_MapX; //! Desplazamiento costado WorldX con respecto screenX.
	int m_MapY; //! Desplazamiento costado WorldY con respecto screenY.

	std::vector < gcn::Point > allPoints; // Puntos Isometricos a dibujar.

	bool validIso( const gcn::Point& p );
	gcn::Point calculaIso( 	int wx,
							int wy );
	gcn::Point calcularRejilla( const gcn::Point& punto );
	gcn::Point tileWalk( 	Direction direction,
							const gcn::Point& fromPoint,
							int puntos = 1 );
};

#endif /* SCROLLER_H_ */
