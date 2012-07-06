/*
 * MenuController.cpp
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#include "menucontroller.h"

#include "menumodel.h"
#include "menuview.h"

MenuController::MenuController( MenuView* view ) :
    Controller < MenuModel, MenuView >( view )
{

}

MenuController::~MenuController()
{

}

void MenuController::keyPressed( gcn::KeyEvent& keyEvent )
{

  switch ( keyEvent.getKey().getValue() )
  {
    case gcn::Key::ESCAPE:

      model().setEnd( MenuModel::QUIT );
      keyEvent.consume();
      break;

    case 'P':
    case 'p':

      model().setEnd( MenuModel::PLAY );
      keyEvent.consume();
      break;

    default:
      break;

  }
}
void MenuController::action( const gcn::ActionEvent& actionEvent )
{

  if ( actionEvent.getId() == "b1" ) {

    view().ActivateOpt();

  } else if ( actionEvent.getId() == "Ok" ) {
    // Cambiar la resolucion
    view().changeResolution();

  } else if ( actionEvent.getId() == "Cancel" ) {
    view().DeactivateOpt();
  }

}
