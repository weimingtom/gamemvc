/*
 * PlayController.cpp
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#include "playcontroller.h"

#include "playmodel.h"
#include "playview.h"

PlayController::PlayController( PlayView* view ) :
    Controller < PlayModel, PlayView >( view )
{

}

PlayController::~PlayController()
{

}
void PlayController::keyPressed( gcn::KeyEvent& keyEvent )
{

  switch ( keyEvent.getKey().getValue() )
  {
    case gcn::Key::ESCAPE:

      model().setEnd( PlayModel::QUIT );
      keyEvent.consume();
      break;

    case 'M':
    case 'm':

      model().setEnd( PlayModel::MENU );
      keyEvent.consume();
      break;

    default:
      break;

  }
}
