/*
 * MenuView.h
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#ifndef MENUVIEW_H_
#define MENUVIEW_H_

#include <memory>

#include "mvc/View.h"

class MenuModel;
class MenuController;

class XmlGui;
namespace gcn {

	class Widget;

}

class MenuView: public View < MenuModel, MenuController >
{
public:
	MenuView( MenuModel* model );
	virtual ~MenuView();

	void initialize();
	void draw();

private:

	std::auto_ptr < XmlGui > xmlgui;
	gcn::Widget* top;

};

#endif /* MENUVIEW_H_ */
