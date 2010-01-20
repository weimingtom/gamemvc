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

#include <MyGame.h>

#include "MenuModel.h"
#include "MenuController.h"

MenuView::MenuView( MenuModel* model ) :
	View < MenuModel, MenuController > ( model ) {

	xmlgui.reset( new XmlGui() );
	xmlgui->parse( "./scripts/gui/Menu/" + Model().game().getResolution().first
			+ "/gui.xml" );
	Model().game().getGui().setTop( top = xmlgui->getWidget( "top" ) );

	top->setFocusable( true );
	top->requestFocus();

	opt = static_cast < gcn::Window* > ( xmlgui->getWidget( "opt" ) );
	optres = static_cast < gcn::DropDown* > ( xmlgui->getWidget( "optres" ) );
	full = static_cast < gcn::CheckBox* > ( xmlgui->getWidget( "full" ) );
}

MenuView::~MenuView() {
	Model().game().getGui().setTop( NULL );
}

void MenuView::initialize() {

	setController( new MenuController( this ) );
	top->addKeyListener( &Controller() );
	xmlgui->getWidget( "optbutton" )->addActionListener( &Controller() );
	xmlgui->getWidget( "Ok" )->addActionListener( &Controller() );
	xmlgui->getWidget( "Cancel" )->addActionListener( &Controller() );

}

void MenuView::draw() {

	Model().game().getGui().draw();
	Model().game().getGui().getGraphics()->pushClipArea( top->getDimension() );

	Model().game().getGui().getGraphics()->setColor( gcn::Color( 0xffffff ) ); // The colour to be used when drawing. From here on, white will be used.
	Model().game().getGui().getGraphics()->drawLine(	10,
														10,
														100,
														100 );
	Model().game().getGui().getGraphics()->drawRectangle( gcn::Rectangle(	0,
																			0,
																			250,
																			250 ) );
	Model().game().getGui().getGraphics()->drawText(	"Texto de prueba",
														10,
														10 );

	Model().game().getGui().getGraphics()->popClipArea();

}
void MenuView::ActivateOpt() {

	opt->setVisible( true );
	opt->requestModalFocus();
	optres->setSelected( Model().getPosResolution() );
	full->setSelected(Model().getResolution().second);

}
void MenuView::DeactivateOpt() {
	opt->releaseModalFocus();
	opt->setVisible( false );
}

void MenuView::changeResolution() {

	std::pair < std::string, bool >
			res( 	optres->getListModel()->getElementAt( optres->getSelected() ),
					full->isSelected() );
	if ( res == Model().getResolution() ) {

		// Se ha seleccionado la misma resolucion que ya teniamos.
		DeactivateOpt(); // Quitamos el windows de opciones.

	} else {

		Model().changeResolution( res );

	}
}
