/*
 * MenuView.cpp
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#include "menuview.h"

#include <functional>

#include <SDL/SDL_gfxPrimitives.h>
#include <guichan.hpp>
#include <guichan/sdl.hpp>
#include <xmlgui.h>

#include <misc/Interface.h>

#include <mygame.h>

#include "menumodel.h"
#include "menucontroller.h"

MenuView::MenuView( MenuModel* model_p ) :
    View < MenuModel, MenuController >( model_p )
{

  xmlgui.reset( new XmlGui() );
  xmlgui->parse( "./scripts/gui/Menu/"
      + model().interface().actualResolution().first + "/gui.xml" );
  model().interface().screen().setTop( top = xmlgui->getWidget( "top" ) );

  top->setFocusable( true );
  top->requestFocus();

  opt = static_cast < gcn::Window* >( xmlgui->getWidget( "opt" ) );
  optres = static_cast < gcn::DropDown* >( xmlgui->getWidget( "optres" ) );
  full = static_cast < gcn::CheckBox* >( xmlgui->getWidget( "full" ) );
}

MenuView::~MenuView()
{
  model().interface().screen().setTop( NULL );
}

void MenuView::Initialize()
{

  controller( new MenuController( this ) );
  top->addKeyListener( &controller() );
  xmlgui->getWidget( "optbutton" )->addActionListener( &controller() );
  xmlgui->getWidget( "Ok" )->addActionListener( &controller() );
  xmlgui->getWidget( "Cancel" )->addActionListener( &controller() );

}

void MenuView::Draw()
{

  model().interface().screen().draw();
  model().interface().screen().getGraphics()->pushClipArea( top->getClipRectangle() );

  model().interface().screen().getGraphics()->setColor( gcn::Color( 0xffffff ) ); // The colour to be used when drawing. From here on, white will be used.
  model().interface().screen().getGraphics()->drawLine( 10,
                                                        10,
                                                        100,
                                                        100 );
  model().interface().screen().getGraphics()->drawRectangle( gcn::Rectangle( 0,
                                                                             0,
                                                                             250,
                                                                             250 ) );
  model().interface().screen().getGraphics()->drawText( "Texto de prueba",
                                                        10,
                                                        10 );
  gcn::SDLGraphics * gr =
      static_cast < gcn::SDLGraphics* >( model().interface().screen().getGraphics() );

  ellipseRGBA( gr->getTarget(),
               100,
               100,
               20,
               10,
               0xFF,
               0x00,
               0x00,
               0xFF );
  model().interface().screen().getGraphics()->popClipArea();

}
void MenuView::ActivateOpt()
{

  opt->setVisible( true );
  opt->requestModalFocus();
  optres->setSelected( model().interface().indexResolution( model().interface().actualResolution().first ) );
  full->setSelected( model().interface().actualResolution().second );

}
void MenuView::DeactivateOpt()
{
  opt->releaseModalFocus();
  opt->setVisible( false );
}

void MenuView::changeResolution()
{

  Interface::ScreenResolutionType res( optres->getListModel()->getElementAt( optres->getSelected() ),
                                       full->isSelected() );
  if ( res == model().interface().actualResolution() ) {

    // Se ha seleccionado la misma resolucion que ya teniamos.
    DeactivateOpt(); // Quitamos el windows de opciones.

  } else {

    model().changeResolution( res );

  }
}
