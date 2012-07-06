/*
 * PlayControllerMsgCenter.cpp
 *
 *  Created on: 16/12/2009
 *      Author: 79481180
 */

#include "playcontrollermsgcenter.h"

#include "playmodel.h"
#include "playviewmsgcenter.h"

//-------------------------------------------------------------------
PlayControllerMsgCenter::PlayControllerMsgCenter( PlayViewMsgCenter* view ) :
    Controller < PlayModel, PlayViewMsgCenter >( view )
{

}

void PlayControllerMsgCenter::mouseMoved( gcn::MouseEvent& mouseEvent )
{

  model().setMouse( "MsgCenter",
                    mouseEvent.getX(),
                    mouseEvent.getY() );
  mouseEvent.consume();

}
void PlayControllerMsgCenter::mouseEntered( gcn::MouseEvent& mouseEvent )
{
  model().setMouse( "MsgCenter",
                    mouseEvent.getX(),
                    mouseEvent.getY() );
  mouseEvent.consume();
}
void PlayControllerMsgCenter::mouseExited( gcn::MouseEvent& mouseEvent )
{
  model().resetMouse();
  mouseEvent.consume();
}
