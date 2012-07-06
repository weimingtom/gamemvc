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

#include <boost/scoped_ptr.hpp>

#include <mvc/View.h>

class MenuModel;
class MenuController;

class Interface;
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

    void Initialize();

    void ActivateOpt();
    void DeactivateOpt();
    void changeResolution();

  private:

    void Draw();

    boost::scoped_ptr < XmlGui > xmlgui;
    gcn::Widget* top; // Container principal.
    gcn::Window* opt; // Ventana para opciones
    gcn::DropDown* optres; // Opciones de resolucion de pantalla.
    gcn::CheckBox* full;

};

#endif /* MENUVIEW_H_ */
