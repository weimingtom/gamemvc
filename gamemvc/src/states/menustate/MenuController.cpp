/*
 * MenuController.cpp
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#include "MenuController.h"

#include "MenuModel.h"
#include "MenuView.h"

MenuController::MenuController( MenuView* view ) :
	Controller < MenuModel, MenuView > ( view ) {

}

MenuController::~MenuController() {

}

void MenuController::keyPressed( gcn::KeyEvent& keyEvent ) {

	switch( keyEvent.getKey().getValue()) {
		case gcn::Key::ESCAPE :

			this->getModel()->setEnd(MenuModel::QUIT);
			keyEvent.consume();
			break;

		case 'P': case 'p':

			this->getModel()->setEnd(MenuModel::PLAY);
			keyEvent.consume();
			break;

		default:
			break;

	}
}
