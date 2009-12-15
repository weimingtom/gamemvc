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
#include "game/Scroller.h"

class PlayModel;
class PlayController;

class XmlGui;
namespace gcn {

	class Widget;
	class TextField;
	class Rectangle;
	class Point;

}

class PlayView: public View < PlayModel, PlayController >
{
public:

	PlayView( PlayModel* model );
	virtual ~PlayView();

	void initialize();
	void draw();

	void setMouse(	const std::string& name,
					const int& X,
					const int& Y );
	void resetMouse();
	void setPressedMouse( 	const int& X,
							const int& Y );
	void setDraggedMouse( const int& X,
	                      const int& Y );
	void setReleasedMouse( 	const int& X,
							const int& Y );
	bool isSelectArea() const;
	const gcn::Rectangle& selectedArea() const;

	XmlGui& getXmlGui() const;

	void moveZone( 	int X,
					int Y );
	void resetMoveZone();
	void moveView( 	int X,
					int Y );

private:

	class Zone
	{
	public:

		Zone( const PlayView& play );
		void initialize();
		void draw();
		void updateMoveView( 	int X,
								int Y );
		void resetMove();

		void moveView( 	int x,
						int y );

	private:

		const PlayView& m_play;
		gcn::Widget* m_zone;
		gcn::Rectangle m_areaZone;
		std::auto_ptr < Scroller > m_scroller;

		bool m_move;
		int moveX;
		int moveY;

		void PaintAllTerrain( const gcn::Point& pLocal );
		void PaintAllBuilding( const gcn::Point& pLocal );
		void PaintAllResource( const gcn::Point& pLocal );
		void PaintAllActor( const gcn::Point& pLocal );

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

	bool			m_selection;		// Seleccion activa?.
	gcn::Point		m_firstselect;		// Primer punto seleccionado;
	gcn::Rectangle	m_selectarea;		// area seleccionada.

	gcn::Widget* top;
	std::auto_ptr < Zone > m_ZoneView;
	std::auto_ptr < PlayMsgLeftView > m_MsgLeftView;
	std::auto_ptr < PlayMsgCenterView > m_MsgCenterView;

};

#endif /* PLAYVIEW_H_ */
