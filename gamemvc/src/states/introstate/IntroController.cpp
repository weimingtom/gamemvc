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

//	LAPP_ <<	"Key pressed: " << keyEvent.getKey().getValue();
	if ( keyEvent.getKey().getValue() == gcn::Key::ESCAPE ) {

		this->getModel()->setFinal(); //! Paramos el bucle asi?.......
		keyEvent.consume();

	}

}
