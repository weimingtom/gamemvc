/*
 * MenuController.h
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#ifndef MENUCONTROLLER_H_
#define MENUCONTROLLER_H_

#include <guichan.hpp>

#include "mvc/Controller.h"

class MenuView;
class MenuModel;

class MenuController:	public Controller < MenuModel, MenuView > ,
						public gcn::KeyListener
{
public:
	MenuController( MenuView* view );
	virtual ~MenuController();

private:

	void keyPressed( gcn::KeyEvent& keyEvent );

};

#endif /* MENUCONTROLLER_H_ */
