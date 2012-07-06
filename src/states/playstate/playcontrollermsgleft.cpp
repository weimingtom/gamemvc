/*
 * PlayControllerMsgLeft.cpp
 *
 *  Created on: 16/12/2009
 *      Author: 79481180
 */

#include "playcontrollermsgleft.h"

#include "playmodel.h"
#include "playviewmsgleft.h"

PlayControllerMsgLeft::PlayControllerMsgLeft( PlayViewMsgLeft* view ) :
    Controller < PlayModel, PlayViewMsgLeft >( view )
{

}

