/*
 * IntroModel.cpp
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#include "IntroModel.h"

#include <stdexcept>
#include <iostream>
#include <boost/ref.hpp>

#include <misc/log.h>

IntroModel::IntroModel() :
	Model(),
	alpha( 255 ),
	m_final( false ),
	m_endtype( IntroModel::CONTINUE ),
	m_control(),
	m_loadInitData( m_control ),
	thr( m_loadInitData ) {

}

IntroModel::~IntroModel() {

	thr.interrupt(); // Si se ha terminado no se atiende....
	thr.join();

}

void IntroModel::Update() {

	alpha--;
	if ( alpha < 0 ) {

		alpha = 0;
		m_final = true; // Marcamos finalizacion bucle video.

	}
	std::string msg;

	if ( m_control.stopWasCommanded() ) {

		if ( m_control.getError() ) throw( std::runtime_error( "Error en thread IntroModel" ) );

		// El Thread ha terminado pero seguimos con el video.....

		msg = "El thread ha terminado ...";
		if ( m_final ) {

			this->setEnd(IntroModel::MENU);
			msg += " y tambien el video";

		} else {

			msg += " pero tenemos video ....";

		}

	} else {

		msg += "Continua el thread .....";

	}
	LAPP_
<<	msg;
}
bool IntroModel::isEnd() {

	return m_endtype != IntroModel::CONTINUE;

}
void IntroModel::setEnd( const IntroModel::EndTypes& type ) {

	m_endtype = type;
}
IntroModel::EndTypes IntroModel::getEnd() const {

	return m_endtype;

}

void IntroModel::setFinal() {

	m_final = true;

}
int IntroModel::getAlpha() {
	return alpha;
}
