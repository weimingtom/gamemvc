#ifndef GOAL_THINK_H
#define GOAL_THINK_H

//-----------------------------------------------------------------------------
//
//  Name:   Goal_Think .h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class to arbitrate between a collection of high level goals, and
//          to process those goals.
//-----------------------------------------------------------------------------
#include <vector>
#include <string>
#include "2d/Vector2D.h"
#include "Goals/Goal_Composite.h"
#include "../CActorMapa.h"

class Goal_Think: public Goal_Composite < CActorMapa >
{

public:

	Goal_Think( CActorMapa* pBot );
	~Goal_Think();

	//this method iterates through each goal evaluator and selects the one
	//that has the highest score as the current goal
	virtual void Arbitrate();

	//returns true if the given goal is not at the front of the subgoal list
	bool notPresent( unsigned int GoalType ) const;

	//the usual suspects
	int Process();
	void Activate();
	void Terminate();

	void Render();

};

#endif
