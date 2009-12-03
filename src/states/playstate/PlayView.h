/*
 * PlayView.h
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#ifndef PLAYVIEW_H_
#define PLAYVIEW_H_

#include <memory>
#include <string>
#include <vector>

#include <guichan.hpp>

#include "mvc/View.h"
#include "misc/Point.h"
#include "game/database/CMouseMapManager.h"

class PlayModel;
class PlayController;

class XmlGui;
namespace gcn {

	class Widget;
	class TextField;

}

class PlayView: public View < PlayModel, PlayController >
{
public:
	PlayView( PlayModel* model );
	virtual ~PlayView();

	void initialize();
	void draw();

	void setMouse(	const std::string& name,
					const int &X,
					const int &Y );
	void resetMouse();

	XmlGui& getXmlGui() const;

	void moveZone( 	int X,
					int Y );
	void resetMoveZone();
	void moveView( 	int X,
					int Y );

private:

	class PlayZoneView
	{
	public:

		PlayZoneView( PlayView& play );
		void initialize();
		void draw();
		void updateMoveView( 	int X,
								int Y );
		void resetMove();

		void moveView( 	int x,
						int y );

	private:

		enum Direction
		{
			NORTH = 0,
			NORTH_EAST,
			EAST,
			SOUTH_EAST,
			SOUTH,
			SOUTH_WEST,
			WEST,
			NORTH_WEST
		};

		PlayView& m_play;
		gcn::Widget* m_zone;

		gcn::Rectangle m_areaZone; //! Dimension del area del widget.
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

		bool m_move;
		int moveX;
		int moveY;

		std::vector < gcn::Point > allPoints; // Puntos Isometricos a dibujar.

		void getPointPaint();

		bool validIso( const gcn::Point& p );
		gcn::Point calculaIso( 	int wx,
								int wy );
		gcn::Point calcularRejilla( const gcn::Point& punto );
		gcn::Point tileWalk( 	Direction direction,
								const gcn::Point& fromPoint,
								int puntos = 1 );
		void PaintAllTerrain( const gcn::Point& paintPoint );
		void PaintAllBuilding( const gcn::Point& paintPoint );

		gcn::Point WorldToScreen( 	int wx,
									int wy );
		gcn::Point WorldToScreen( const gcn::Point& p );
		gcn::Point LocalToWorld( 	int lX,
									int lY );
		gcn::Point LocalToScreen( 	int lX,
									int lY );

	};
	class PlayMsgLeftView
	{
	public:

		PlayMsgLeftView( PlayView& play );
		void initialize();
		void draw();

		void setName( const std::string& text );
		void setPosX( const std::string& x );
		void setPosY( const std::string& y );

	private:

		PlayView& m_play;

		gcn::TextField* m_name;
		gcn::TextField* m_posX;
		gcn::TextField* m_posY;

	};
	class PlayMsgCenterView
	{
	public:

		PlayMsgCenterView( PlayView& play );
		void initialize();
		void draw();

	private:

		PlayView& m_play;
		gcn::Widget* m_msgcenter;

	};

	std::auto_ptr < XmlGui > xmlgui;

	gcn::Widget* top;
	std::auto_ptr < PlayZoneView > m_ZoneView;
	std::auto_ptr < PlayMsgLeftView > m_MsgLeftView;
	std::auto_ptr < PlayMsgCenterView > m_MsgCenterView;

};

#endif /* PLAYVIEW_H_ */
