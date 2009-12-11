/*
 * Goal_Think_wrapper.h
 *
 *  Created on: 10-dic-2008
 *      Author: 79481180
 */

#ifndef GOAL_THINK_WRAPPER_H_
#define GOAL_THINK_WRAPPER_H_

struct Goal_Think_wrapper:  Goal_Think, luabind::wrap_base
{
	Goal_Think_wrapper( CActorMapa* pBot ) :
		Goal_Think( pBot ) {

	}
	void Arbitrate() {

		call_member < void > ( this, "Arbitrate" );

	}

	static void default_Arbitrate(Goal_Think* ptr ) {

		 ptr->Goal_Think::Arbitrate();

		 return;
	}
	virtual ~Goal_Think_wrapper(){

	}
};

#endif /* GOAL_THINK_WRAPPER_H_ */
