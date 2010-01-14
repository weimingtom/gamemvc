/*
 * PlayControllerMsgCenter.cpp
 *
 *  Created on: 16/12/2009
 *      Author: 79481180
 */

#include "PlayControllerMsgCenter.h"

#include "PlayModel.h"
#include "PlayViewMsgCenter.h"

//-------------------------------------------------------------------
PlayControllerMsgCenter::PlayControllerMsgCenter( PlayViewMsgCenter* view ) :
	Controller < PlayModel, PlayViewMsgCenter > ( view ) {

}

void PlayControllerMsgCenter::mouseMoved( gcn::MouseEvent& mouseEvent ) {

	Model().setMouse(	"MsgCenter",
						mouseEvent.getX(),
						mouseEvent.getY() );
	mouseEvent.consume();

}
void PlayControllerMsgCenter::mouseEntered( gcn::MouseEvent& mouseEvent ) {
	Model().setMouse(	"MsgCenter",
						mouseEvent.getX(),
						mouseEvent.getY() );
	mouseEvent.consume();
}
void PlayControllerMsgCenter::mouseExited( gcn::MouseEvent& mouseEvent ) {
	Model().resetMouse();
	mouseEvent.consume();
}
