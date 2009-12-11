/*
 * Goal_Wander_wrapper.h
 *
 *  Created on: 16-dic-2008
 *      Author: 79481180
 */

#ifndef GOAL_WANDER_WRAPPER_H_
#define GOAL_WANDER_WRAPPER_H_

struct Goal_Wander_wrapper : Goal_Wander,  luabind::wrap_base
{
	Goal_Wander_wrapper( CActorMapa* pBot ) :
		Goal_Wander(pBot){

	}
	virtual ~Goal_Wander_wrapper(){

	}
};

#endif /* GOAL_WANDER_WRAPPER_H_ */
