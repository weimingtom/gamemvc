/*
 * IntroView.cpp
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */
#include "IntroView.h"

#include <iostream>
#include <iomanip>

#include <guichan.hpp>
#include "xmlgui.h"

#include "MyGame.h"
#include "IntroModel.h"
#include "IntroController.h"

IntroView::IntroView( IntroModel* model ) :
	View < IntroModel, IntroController > ( model ) {

	xmlgui.reset( new XmlGui() );
	xmlgui->parse( "./scripts/Intro/gui.xml" );

	game.getGui().setTop( top = xmlgui->getWidget( "top" ) );
	top->setFocusable( true );
	top->requestFocus();

	text = static_cast < gcn::TextField* > ( xmlgui->getWidget( "text" ) );
	text->adjustSize();
	text->setFocusable( false );

}

IntroView::~IntroView() {

	game.getGui().setTop( NULL );

}

void IntroView::initialize() {

	m_controller = new IntroController( this );
	top->addKeyListener( m_controller );

}

void IntroView::draw() {

	std::ostringstream stm;

	// Output an int
	stm << setfill( '0' ) << setw( 5 ) << this->getModel()->getAlpha();
	text->setText( stm.str() );
	game.getGui().draw();

}
