/*
 * MenuView.cpp
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#include "MenuView.h"

#include <guichan.hpp>
#include "xmlgui.h"

#include "MyGame.h"
#include "MenuModel.h"
#include "MenuController.h"

MenuView::MenuView( MenuModel* model ) :
	View < MenuModel, MenuController > ( model ) {

	xmlgui.reset( new XmlGui() );
	xmlgui->parse( "./scripts/Menu/gui.xml" );
	game.getGui().setTop( top = xmlgui->getWidget( "top" ) );

	top->setFocusable( true );
	top->requestFocus();

}

MenuView::~MenuView() {

	game.getGui().setTop( NULL );

}

void MenuView::initialize() {

	m_controller = new MenuController( this );
	top->addKeyListener( m_controller );

}

void MenuView::draw() {

	game.getGui().draw();

	game.getGui().getGraphics()->_beginDraw();

	game.getGui().getGraphics()->setColor( gcn::Color( 0xffffff ) ); // The colour to be used when drawing. From here on, white will be used.
	game.getGui().getGraphics()->drawLine( 10,
											10,
											100,
											100 );
	game.getGui().getGraphics()->drawRectangle( gcn::Rectangle(	0,
																	0,
																	250,
																	250 ) );
	game.getGui().getGraphics()->drawText( "Texto de prueba",
											10,
											10 );
	game.getGui().getGraphics()->_endDraw();

}
