/*
 * PlayViewZone.h
 *
 *  Created on: 15/12/2009
 *      Author: uberiain
 */

#ifndef PLAYVIEWZONE_H_
#define PLAYVIEWZONE_H_

#include <guichan.hpp>

#include <IsoHex/IMap.hpp>
#include <IsoHex/MouseMap.hpp>
#include <IsoHex/Scroller.hpp>

#include <mvc/View.h>

class PlayControllerZone;
class PlayModel;
class XmlGui;

class PlayViewZone: public View < PlayModel, PlayControllerZone >
{
public:

	PlayViewZone( 	PlayModel* model,
					XmlGui& xmlgui );
	virtual ~PlayViewZone();
	void initialize();
	void draw();

	void Scroll( 	int screenExtent,
					IMap::Direction screenDirection );

	void updateMoveView( 	int X,
							int Y );
	void resetMove();

	void moveView( 	int x,
					int y );

	void setPressedMouse( 	const int& X,
							const int& Y );

	void setDraggedMouse( 	const int& X,
							const int& Y );

	void setReleasedMouse( 	const int& X,
							const int& Y );

private:

	gcn::Widget* 				m_zone;
	gcn::Rectangle				m_areaZone;
	IMouseMapPtrType ptMouseMap;
	gcn::Point		 m_tileAnchor;
	IMapPtrType	 	 ptIsoMap;
	ScrollerPtrType	 ptScroller;


	bool m_move;
	int moveX;
	int moveY;

	bool 			m_selection; // Seleccion activa?.
	gcn::Point 		m_firstselect; // Primer punto seleccionado;
	gcn::Rectangle	m_selectarea; // area seleccionada.

	void PaintAllTerrain( const gcn::Point& pLocal );
	void PaintAllBuilding( const gcn::Point& pLocal );
	void PaintAllResource( const gcn::Point& pLocal );
	void PaintAllActor( const gcn::Point& pLocal );
};

#endif /* PLAYVIEWZONE_H_ */
