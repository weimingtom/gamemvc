/*
 * IntroView.cpp
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */
#include "introview.h"

#include <iostream>
#include <iomanip>

#include <guichan.hpp>
#include <xmlgui.h>

#include "intromodel.h"
#include "introcontroller.h"

IntroView::IntroView( IntroModel* model_p ) :
    View < IntroModel, IntroController >( model_p )
{

  xmlgui_.reset( new XmlGui() );
  xmlgui_->parse( "./scripts/gui/Intro/" + model().resolution().first
      + "/gui.xml" );

  model().screen().setTop( top_ = xmlgui_->getWidget( "top" ) );
  top_->setFocusable( true );
  top_->requestFocus();

  text_ = static_cast < gcn::TextField* >( xmlgui_->getWidget( "text" ) );
  text_->adjustSize();
  text_->setFocusable( false );

}

IntroView::~IntroView()
{

  model().screen().setTop( NULL );
}

void IntroView::Initialize()
{

  controller( new IntroController( this ) );
  top_->addKeyListener( &controller() );

}

void IntroView::Draw()
{

  std::stringstream stm;

  // Output an int
  stm << std::setfill( '0' ) << std::setw( 5 ) << model().alpha();
  text_->setText( stm.str() );
  model().screen().draw();

}
