/*
 * IntroController.h
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#ifndef INTROCONTROLLER_H_
#define INTROCONTROLLER_H_

#include <guichan.hpp>

#include "mvc/Controller.h"

class IntroView;
class IntroModel;

class IntroController:	public Controller < IntroModel, IntroView > ,
						public gcn::KeyListener
{
public:

	IntroController( IntroView* view );
	virtual ~IntroController();

private:

	void keyPressed( gcn::KeyEvent& keyEvent );

};

#endif /* INTROCONTROLLER_H_ */
