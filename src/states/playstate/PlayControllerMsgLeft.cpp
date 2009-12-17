/*
 * PlayControllerMsgLeft.cpp
 *
 *  Created on: 16/12/2009
 *      Author: 79481180
 */

#include "PlayControllerMsgLeft.h"

#include "PlayModel.h"
#include "PlayViewMsgLeft.h"

PlayControllerMsgLeft::PlayControllerMsgLeft( PlayViewMsgLeft* view ) :
	Controller < PlayModel, PlayViewMsgLeft > ( view ) {

}

