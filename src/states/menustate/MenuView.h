/*
 * MenuView.h
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#ifndef MENUVIEW_H_
#define MENUVIEW_H_

#include <memory>
#include <string>

#include "mvc/View.h"

class MenuModel;
class MenuController;

class XmlGui;
namespace gcn {

	class Widget;
	class Window;
	class DropDown;
	class CheckBox;

}

class MenuView: public View < MenuModel, MenuController >
{
public:
	MenuView( MenuModel* model );
	virtual ~MenuView();

	void initialize();
	void draw();

	void ActivateOpt();
	void DeactivateOpt();
	void changeResolution();

private:

	std::auto_ptr < XmlGui > xmlgui;
	gcn::Widget* 	top;		// Container principal.
	gcn::Window*	opt;		// Ventana para opciones
	gcn::DropDown*	optres;		// Opciones de resolucion de pantalla.
	gcn::CheckBox*	full;

};

#endif /* MENUVIEW_H_ */
