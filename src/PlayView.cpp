/*
 * PlayView.cpp
 *
 *  Created on: 04/01/2010
 *      Author: 79481180
 */

const int MAPWIDTH = 20;
const int MAPHEIGHT = 20;

#include "PlayView.h"

#include <windows.h>

#include <IsoHex/MapFactory.hpp>

#include "Game.h"

#include "PlayModel.h"
#include "PlayController.h"

const int kPadding = 0;

PlayView::PlayView( PlayModel* model ) :
    View < PlayModel, PlayController > ( model ), ptCursor( 0,
                                                            0 ),
            m_paint_( 192,
                      144,
                      640,
                      480 ),
            m_padding_( kPadding ) {

    top = new gcn::Container();
    top->setDimension( gcn::Rectangle( 0,
                                       0,
                                       1024,
                                       768 ) );
    game.getGui().setTop( top );

    label = new gcn::Label( "Hello World" );
    label->setPosition( 140,
                        110 );
    top->add( label );

    // Obtener el rectangulo donde pintar, la posicion absoluta con
    // respecto al cuadro de pantalla ( screen ), usado en las funciones de
    // dibujo.

    top->getAbsolutePosition( m_absPos.x,
                              m_absPos.y );
    m_absPos.width = top->getWidth();
    m_absPos.height = top->getHeight();

    // Cargar datos para el dibujo....
    // El Tile.
    // El cursor.
    // El mousemap.
    // La clase para el manejo del mapa.

    top->setFocusable( true );
    top->requestFocus();

    CreateMap( IMap::SQUARED_MAP_TYPE ); // Creamos mapa por defecto.

}

PlayView::~PlayView() {

}
void PlayView::initialize() {

    setController( new PlayController( this ) );
    top->addKeyListener( &Controller() );
    top->addMouseListener( &Controller() );

}

void PlayView::draw() {

    game.getGui().getGraphics()->pushClipArea( m_absPos );

    DrawMap();

    ShowIsoCursor();

    game.getGui().getGraphics()->drawRectangle( m_paint_ );

    game.getGui().getGraphics()->popClipArea();

}

void PlayView::MoveCursor( IMap::Direction Dir ) {

    gcn::Point ptTemp = ptScroller->move( ptCursor,
                                          Dir );
    //clip cursor to tilemap

    //bounds checking
    //x<0
    if ( ptTemp.x < 0 ) ptTemp = ptCursor;

    //y<0
    if ( ptTemp.y < 0 ) ptTemp = ptCursor;

    //x>MAPWIDTH-1
    if ( ptTemp.x > ( MAPWIDTH - 1 ) ) ptTemp = ptCursor;

    //y>MAPHEIGHT-1
    if ( ptTemp.y > ( MAPHEIGHT - 1 ) ) ptTemp = ptCursor;

    //assign new cursor position
    ptCursor = ptTemp;

    ptScroller->center( ptScroller->plot( ptCursor ) );

}
void PlayView::Scroll( int screenExtent,
                       IMap::Direction screenDirection ) {

    ptScroller->scroll( screenExtent,
                        screenDirection );

}
void PlayView::MoveMouse( int x,
                          int y ) {
    /*
     gcn::Point ptMouse;
     ptMouse.x = x;
     ptMouse.y = y;
     //mousemap the mouse coordinates
     ptCursor = ptScroller->map( ptMouse );

     //clip cursor to tilemap
     if ( ptCursor.x < 0 ) ptCursor.x = 0;
     if ( ptCursor.y < 0 ) ptCursor.y = 0;
     if ( ptCursor.x > MAPWIDTH - 1 ) ptCursor.x = MAPWIDTH - 1;
     if ( ptCursor.y > MAPHEIGHT - 1 ) ptCursor.y = MAPHEIGHT - 1;

     //check for scrolling zones

     //top
     if ( ptMouse.y < 8 ) {
     ptScroller->Scroll( ( 8 - ptMouse.y ),
     IMap::NORTH );
     }
     //bottom
     if ( ptMouse.y > ( m_paint_.height - 8 ) ) {
     ptScroller->Scroll( ptMouse.y - ( m_paint_.height - 8 ),
     IMap::SOUTH );
     }
     //left
     if ( ptMouse.x < 8 ) {
     ptScroller->Scroll( ( 8 - ptMouse.x ),
     IMap::WEST );
     }
     //right
     if ( ptMouse.x > ( m_paint_.width - 8 ) ) {
     ptScroller->Scroll( ( ptMouse.x - (  m_paint_.width - 8 ) ),
     IMap::EAST );
     }
     //	ptScroller->Center(ptScroller->plot(ptCursor));

     */
}

void PlayView::CreateMap( IMap::MapType type ) {

    switch ( type ) {

        case IMap::ISO_DIAMOND_MAP_TYPE:
        case IMap::ISO_SLIDE_MAP_TYPE:
        case IMap::ISO_STAGGERED_MAP_TYPE:

            Model().getTileIso();
            tsCursor.reset( new Tile( "cur_iso_64.png" ) );
            ptMouseMap.reset( new MouseMap( "iso_64.bmp" ) );

            break;

        case IMap::HEX_DIAMOND_MAP_TYPE:
        case IMap::HEX_STAGGERED_MAP_TYPE:
        case IMap::HEX_SLIDE_MAP_TYPE:

            Model().getTileHex();
            tsCursor.reset( new Tile( "cur_hex_64.png" ) );
            ptMouseMap.reset( new MouseMap( "hex_64.bmp" ) );

            break;

        case IMap::SQUARED_MAP_TYPE:

            Model().getTileSquared();
            tsCursor.reset( new Tile( "cur_squared_64.png" ) );
            ptMouseMap.reset( new MouseMap( "squared_64.bmp" ) );

            break;

    }

    ptIsoMap.reset( new MapFactory( type,
                                    *ptMouseMap ) );
    ptScroller.reset( new Scroller( *ptIsoMap,
                                    gcn::Rectangle( 0,
                                                    0,
                                                    MAPWIDTH,
                                                    MAPHEIGHT ),
                                    m_paint_,
                                    gcn::Point(ptMouseMap->w()/2,ptMouseMap->h()/2),
                                    /*
                                    gcn::Point( tsCursor->getWidth()/2,
                                                tsCursor->getHeight()/2 ),
                                    */
                                    m_padding_ ) );

    ptScroller->center( ptScroller->plot( gcn::Point( 0,
                                                      0 ) ) );

}

//-------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------
void PlayView::DrawMap() {

    Scroller::iterator it;
    for ( it = ptScroller->begin(); it != ptScroller->end(); ++it ) {

        gcn::Point ptPlot = ptScroller->plot( *it );

        Model().draw( game.getGui().getGraphics(),
                      ptPlot );

    }

}

void PlayView::ShowIsoCursor() {

    //copy cursor position
    gcn::Point ptMap = ptCursor;

    //plot cursor position
    gcn::Point ptPlot = ptScroller->plot( ptMap );

    //put the cursor image
    tsCursor->draw( game.getGui().getGraphics(),
                    ptPlot );

}

