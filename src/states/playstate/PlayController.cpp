/*
 * PlayController.cpp
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#include "PlayController.h"

#include "PlayModel.h"
#include "PlayView.h"

PlayController::PlayController( PlayView* view ) :
	Controller < PlayModel, PlayView > ( view ), zoneMouseListener( this ),
			msgcenterMouseListener( this ) {

}

PlayController::~PlayController() {

}
gcn::MouseListener* PlayController::getZoneMouseListener() {

	return &zoneMouseListener;

}
gcn::MouseListener* PlayController::getMsgCenterMouseListener() {

	return &msgcenterMouseListener;

}
void PlayController::keyPressed( gcn::KeyEvent& keyEvent ) {

	switch ( keyEvent.getKey().getValue() ) {
		case gcn::Key::ESCAPE:

			this->getModel()->setEnd( PlayModel::QUIT );
			keyEvent.consume();
		break;

		case 'M':
		case 'm':

			this->getModel()->setEnd( PlayModel::MENU );
			keyEvent.consume();
		break;

		default:
		break;

	}
}
//-------------------------------------------------------------------
PlayController::Zone::Zone( PlayController* play ) :
	m_play( play ) {

}
void PlayController::Zone::mouseMoved( gcn::MouseEvent& mouseEvent ) {

	m_play->getView()->setMouse(	"Zone",
									mouseEvent.getX(),
									mouseEvent.getY() );
	m_play->getView()->moveZone( 	mouseEvent.getX(),
									mouseEvent.getY() );
	mouseEvent.consume();

}
void PlayController::Zone::mouseEntered( gcn::MouseEvent& mouseEvent ) {

	m_play->getView()->setMouse(	"Zone",
									mouseEvent.getX(),
									mouseEvent.getY() );
	m_play->getView()->moveZone( 	mouseEvent.getX(),
									mouseEvent.getY() );
	mouseEvent.consume();

}
void PlayController::Zone::mouseExited( gcn::MouseEvent& mouseEvent ) {

	m_play->getView()->resetMouse();
	m_play->getView()->resetMoveZone();
	mouseEvent.consume();

}
//-------------------------------------------------------------------
PlayController::MsgCenter::MsgCenter( PlayController* play ) :
	m_play( play ) {

}

void PlayController::MsgCenter::mouseMoved( gcn::MouseEvent& mouseEvent ) {

	m_play->getView()->setMouse(	"MsgCenter",
									mouseEvent.getX(),
									mouseEvent.getY() );
	mouseEvent.consume();

}
void PlayController::MsgCenter::mouseEntered( gcn::MouseEvent& mouseEvent ) {
	m_play->getView()->setMouse(	"MsgCenter",
									mouseEvent.getX(),
									mouseEvent.getY() );
	mouseEvent.consume();
}
void PlayController::MsgCenter::mouseExited( gcn::MouseEvent& mouseEvent ) {
	m_play->getView()->resetMouse();
	mouseEvent.consume();
}
