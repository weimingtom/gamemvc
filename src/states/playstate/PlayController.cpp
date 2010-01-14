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
	Controller < PlayModel, PlayView > ( view ){

}

PlayController::~PlayController() {

}
void PlayController::keyPressed( gcn::KeyEvent& keyEvent ) {

	switch ( keyEvent.getKey().getValue() ) {
		case gcn::Key::ESCAPE:

			Model().setEnd( PlayModel::QUIT );
			keyEvent.consume();
		break;

		case 'M':
		case 'm':

			Model().setEnd( PlayModel::MENU );
			keyEvent.consume();
		break;

		default:
		break;

	}
}
