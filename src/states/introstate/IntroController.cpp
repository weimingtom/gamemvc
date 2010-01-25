/*
 * IntroController.cpp
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */
#include "IntroController.h"

#include <stdexcept>
#include <tinyxml.h>

#include "IntroModel.h"
#include "IntroView.h"

IntroController::IntroController( IntroView* view ) :
	Controller < IntroModel, IntroView > ( view ) {

}

IntroController::~IntroController() {

}

void IntroController::keyPressed( gcn::KeyEvent& keyEvent ) {

	if ( keyEvent.getKey().getValue() == gcn::Key::ESCAPE ) {

		Model().setFinal(); //! Paramos el bucle asi?.......
		keyEvent.consume();

	}

}
