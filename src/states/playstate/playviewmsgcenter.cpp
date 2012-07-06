/*
 * PlayViewMsgCenter.cpp
 *
 *  Created on: 16/12/2009
 *      Author: 79481180
 */

#include "playviewmsgcenter.h"

#include <xmlgui.h>

#include <misc/Interface.h>
#include <mygame.h>

#include "playmodel.h"
#include "playview.h"
#include "playcontrollermsgcenter.h"

//-------------------------------------------------------------------
//
// PlayViewMsgCenter
//
PlayViewMsgCenter::PlayViewMsgCenter( PlayModel* model_p,
                                      XmlGui& xmlgui ) :
    View < PlayModel, PlayControllerMsgCenter >( model_p ), m_interface_( model().interface() ), m_msgcenter( xmlgui.getWidget( "msgcenter" ) ), m_pos( m_msgcenter->getClipRectangle() )
{

}
void PlayViewMsgCenter::Initialize()
{

  controller( new PlayControllerMsgCenter( this ) );
  m_msgcenter->addMouseListener( &controller() );

}
void PlayViewMsgCenter::Draw()
{

  //
  // Pintamos la parte del MsgCenter
  //
  m_interface_.screen().getGraphics()->pushClipArea( m_pos );
  m_interface_.screen().getGraphics()->setColor( gcn::Color( 0xffffff ) ); // The colour to be used when drawing. From here on, white will be used.
  m_interface_.screen().getGraphics()->drawLine( 10,
                                                 10,
                                                 100,
                                                 100 );
  m_interface_.screen().getGraphics()->drawText( "Otro texto de prueba",
                                                 15,
                                                 15 );
  m_interface_.screen().getGraphics()->popClipArea();

}
