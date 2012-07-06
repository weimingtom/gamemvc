/*
 * PlayView.cpp
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#include "playview.h"

#include <algorithm>
#include <functional>
#include <sstream>
#include <guichan.hpp>
#include <xmlgui.h>

#include <misc/Interface.h>
#include <misc/debug.h>

#include <mygame.h>

#include "playmodel.h"
#include "playcontroller.h"

#include "playviewzone.h"
#include "playviewmsgleft.h"
#include "playviewmsgcenter.h"

#include "playcontrollerzone.h"
#include "playcontrollermsgleft.h"
#include "playcontrollermsgcenter.h"

PlayView::PlayView( PlayModel* model_p ) :
    View < PlayModel, PlayController >( model_p )
{

  xmlgui.reset( new XmlGui() );
  xmlgui->parse( "./scripts/gui/Play/"
      + model().interface().actualResolution().first + "/gui.xml" );
  model().interface().screen().setTop( top = xmlgui->getWidget( "top" ) );

  top->requestFocus();

  zoneview_.reset( new PlayViewZone( model_p,
                                     *xmlgui ) );
  msgleftview_.reset( new PlayViewMsgLeft( model_p,
                                           *xmlgui ) );
  msgcenterview_.reset( new PlayViewMsgCenter( model_p,
                                               *xmlgui ) );

}

PlayView::~PlayView()
{

  delete msgcenterview_->controller( NULL );
  delete msgleftview_->controller( NULL );
  delete zoneview_->controller( NULL );

  model().interface().screen().setTop( NULL );

}

void PlayView::Initialize()
{

  controller( new PlayController( this ) );
  top->addKeyListener( &controller() );

  zoneview_->Initialize();
  msgleftview_->Initialize();
  msgcenterview_->Initialize();

}

void PlayView::Draw()
{

  if ( model().ismouse() ) {

    msgleftview_->setMsgLeftname( model().getMsgLeftname() );
    msgleftview_->setMsgLeftX( model().getMsgLeftX() );
    msgleftview_->setMsgLeftY( model().getMsgLeftY() );

  } else {

    msgleftview_->resetMsgLeft();

  }
  model().interface().screen().draw();

}
