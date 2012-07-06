/*
 * PlayControllerMsgCenter.h
 *
 *  Created on: 16/12/2009
 *      Author: 79481180
 */

#ifndef PLAYCONTROLLERMSGCENTER_H_
#define PLAYCONTROLLERMSGCENTER_H_

#include <guichan.hpp>
#include <mvc/Controller.h>

class PlayModel;
class PlayViewMsgCenter;

class PlayControllerMsgCenter: public Controller < PlayModel, PlayViewMsgCenter >,
                               public gcn::MouseListener
{
  public:

    PlayControllerMsgCenter( PlayViewMsgCenter* view );
    void mouseMoved( gcn::MouseEvent& mouseEvent );
    void mouseEntered( gcn::MouseEvent& mouseEvent );
    void mouseExited( gcn::MouseEvent& mouseEvent );

};

#endif /* PLAYCONTROLLERMSGCENTER_H_ */
