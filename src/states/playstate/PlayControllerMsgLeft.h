/*
 * PlayControllerMsgLeft.h
 *
 *  Created on: 16/12/2009
 *      Author: 79481180
 */

#ifndef PLAYCONTROLLERMSGLEFT_H_
#define PLAYCONTROLLERMSGLEFT_H_

#include <mvc/Controller.h>

class PlayModel;
class PlayViewMsgLeft;

class PlayControllerMsgLeft: public Controller < PlayModel, PlayViewMsgLeft >
{
public:

	PlayControllerMsgLeft( PlayViewMsgLeft* view );

};

#endif /* PLAYCONTROLLERMSGLEFT_H_ */
