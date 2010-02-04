/*
 * PlayView.h
 *
 *  Created on: 04/01/2010
 *      Author: 79481180
 */

#ifndef PLAYVIEW_H_
#define PLAYVIEW_H_

#include <memory>
#include <guichan.hpp>

#include <IsoHex/IMap.hpp>
#include <IsoHex/MouseMap.hpp>
#include <IsoHex/Scroller.hpp>

#include <mvc/View.h>

class PlayModel;
class PlayController;

#include "Tile.h"

class PlayView: public View < PlayModel, PlayController >
{
public:

	PlayView( PlayModel* model );
	virtual ~PlayView();

	virtual void initialize();
	virtual void draw();

	void MoveCursor( IMap::Direction Dir );
	void MoveMouse( int x,
					int y );
	void Scroll( 	int screenExtent,
					IMap::Direction screenDirection );
	void CreateMap( IMap::MapType type );

private:

	void DrawMap();
	void ShowIsoCursor();
	gcn::Point mouseMapper( gcn::Point ptMouse ) const;

	gcn::Container* top;
	gcn::Label* label;

	gcn::Rectangle m_absPos;

	gcn::Point ptCursor;



	std::auto_ptr < Tile > tsCursor;
	IMouseMapPtrType ptMouseMap;
	ScrollerPtrType ptScroller;
	IMapPtrType ptIsoMap;

	const gcn::Rectangle m_paint_;
	const int 			m_padding_;

};

#endif /* PLAYVIEW_H_ */
