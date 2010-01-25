/*
 * MenuView.cpp
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#include "MenuView.h"

#include <functional>

#include <guichan.hpp>
#include <xmlgui.h>

#include <misc/Interface.h>

#include <MyGame.h>

#include "MenuModel.h"
#include "MenuController.h"

MenuView::MenuView( MenuModel* model ) :
	View < MenuModel, MenuController > ( model ),
	m_interface_(Model().interface()){

	xmlgui.reset( new XmlGui() );
	xmlgui->parse( "./scripts/gui/Menu/" + m_interface_.actualResolution().first
			+ "/gui.xml" );
	m_interface_.screen().setTop( top = xmlgui->getWidget( "top" ) );

	top->setFocusable( true );
	top->requestFocus();

	opt = static_cast < gcn::Window* > ( xmlgui->getWidget( "opt" ) );
	optres = static_cast < gcn::DropDown* > ( xmlgui->getWidget( "optres" ) );
	full = static_cast < gcn::CheckBox* > ( xmlgui->getWidget( "full" ) );
}

MenuView::~MenuView() {
	m_interface_.screen().setTop( NULL );
}

void MenuView::initialize() {

	setController( new MenuController( this ) );
	top->addKeyListener( &Controller() );
	xmlgui->getWidget( "optbutton" )->addActionListener( &Controller() );
	xmlgui->getWidget( "Ok" )->addActionListener( &Controller() );
	xmlgui->getWidget( "Cancel" )->addActionListener( &Controller() );

}

void MenuView::draw() {

	m_interface_.screen().draw();
	m_interface_.screen().getGraphics()->pushClipArea( top->getDimension() );

	m_interface_.screen().getGraphics()->setColor( gcn::Color( 0xffffff ) ); // The colour to be used when drawing. From here on, white will be used.
	m_interface_.screen().getGraphics()->drawLine(	10,
														10,
														100,
														100 );
	m_interface_.screen().getGraphics()->drawRectangle( gcn::Rectangle(	0,
																			0,
																			250,
																			250 ) );
	m_interface_.screen().getGraphics()->drawText(	"Texto de prueba",
														10,
														10 );

	m_interface_.screen().getGraphics()->popClipArea();

}
void MenuView::ActivateOpt() {

	opt->setVisible( true );
	opt->requestModalFocus();
	optres->setSelected( m_interface_.indexResolution(m_interface_.actualResolution().first) );
	full->setSelected( m_interface_.actualResolution().second );

}
void MenuView::DeactivateOpt() {
	opt->releaseModalFocus();
	opt->setVisible( false );
}

void MenuView::changeResolution() {

	Interface::ScreenResolutionType
			res( 	optres->getListModel()->getElementAt( optres->getSelected() ),
					full->isSelected() );
	if ( res == m_interface_.actualResolution() ) {

		// Se ha seleccionado la misma resolucion que ya teniamos.
		DeactivateOpt(); // Quitamos el windows de opciones.

	} else {

		Model().changeResolution( res );

	}
}
