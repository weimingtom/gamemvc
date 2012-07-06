/*
 * PlayViewMsgLeft.cpp
 *
 *  Created on: 16/12/2009
 *      Author: 79481180
 */

#include "playviewmsgleft.h"

#include <sstream>
#include <xmlgui.h>

#include <mygame.h>

#include "playmodel.h"
#include "playview.h"
#include "playcontrollermsgleft.h"

//-------------------------------------------------------------------
//
// PlayViewMsgLeft
//
PlayViewMsgLeft::PlayViewMsgLeft( PlayModel* model,
                                  XmlGui& xmlgui ) :
    View < PlayModel, PlayControllerMsgLeft >( model ), m_msgleft( xmlgui.getWidget( "msgleft" ) ), m_name( static_cast < gcn::TextField* >( xmlgui.getWidget( "name" ) ) ), m_posX( static_cast < gcn::TextField* >( xmlgui.getWidget( "X" ) ) ), m_posY( static_cast < gcn::TextField* >( xmlgui.getWidget( "Y" ) ) )
{

}
void PlayViewMsgLeft::Initialize()
{

}
void PlayViewMsgLeft::setMsgLeftname( const std::string& name )
{

  m_name->setText( name );

}
void PlayViewMsgLeft::setMsgLeftX( const int& X )
{

  std::stringstream ox;
  ox << X;
  m_posX->setText( ox.str() );

}
void PlayViewMsgLeft::setMsgLeftY( const int& Y )
{

  std::stringstream oy;
  oy << Y;
  m_posY->setText( oy.str() );

}
void PlayViewMsgLeft::resetMsgLeft()
{

  m_name->setText( "" );
  m_posX->setText( "" );
  m_posY->setText( "" );

}
void PlayViewMsgLeft::Draw()
{

}

