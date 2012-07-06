/*
 * PlayViewZone.h
 *
 *  Created on: 15/12/2009
 *      Author: uberiain
 */

#ifndef PLAYVIEWZONE_H_
#define PLAYVIEWZONE_H_

#include <guichan.hpp>

#include <isohex/IMap.hpp>
#include <isohex/MouseMap.hpp>
#include <isohex/Scroller.hpp>

#include <mvc/View.h>

#include "cactormapa.h"

class Interface;
class PlayControllerZone;
class PlayModel;
class XmlGui;
class SDLgdi;

class PlayViewZone: public View < PlayModel, PlayControllerZone >
{
  public:

    PlayViewZone( PlayModel* model,
                  XmlGui& xmlgui );
    virtual ~PlayViewZone();
    void Initialize();

    void Render();

    void Scroll( int screenExtent,
                 IMap::Direction screenDirection );

    void updateMoveView( int X,
                         int Y );
    void resetMove();

    void moveView( int x,
                   int y );

    void paintSelectedArea( const gcn::Rectangle area );
    void setSelectedArea( const gcn::Rectangle& area );
    void setDestination( const gcn::Rectangle& area );
    const gcn::Rectangle& area() const;

  private:

    const Interface& m_interface_;

    gcn::Widget* m_zone;
    gcn::Rectangle m_areaZone;
    gcn::Rectangle m_pos;
    IMouseMapPtrType ptMouseMap;
    gcn::Point m_tileAnchor;
    IMapPtrType ptIsoMap;
    ScrollerPtrType ptScroller;

    bool m_move;
    int moveX;
    int moveY;

    bool m_selection;
    gcn::Rectangle m_selectarea;

//	std::vector < CActorMapa* > m_ActorSelected;

    SDLgdi* m_sdlgdi_;

    void Draw();

    void PaintAllTerrain( const gcn::Point& pLocal );
    void PaintAllBuilding( const gcn::Point& pLocal );
    void PaintAllResource( const gcn::Point& pLocal );
    void PaintAllActor( const gcn::Point& pLocal );

    void PaintAll( const gcn::Point& pMap );

    void selectActor( CActorMapa* actor );
    void clearSelectActor();

};

#endif /* PLAYVIEWZONE_H_ */
