/*
 * Goal_Stopped.h
 *
 *  Created on: 04-dic-2008
 *      Author: 79481180
 */

#ifndef GOAL_STOPPED_H_
#define GOAL_STOPPED_H_

#include "Goals/Goal.h"
#include "../CActorMapa.h"

class Goal_Stopped: public Goal < CActorMapa >
{
public:
        Goal_Stopped( CActorMapa* pBot , double time);
        //the usual suspects
        void Activate();
        int Process();
        void Terminate();

private:

        //this records the time this goal was activated
        double m_dStartTime;

        //time to wait at stopped.
        double m_dWaitTime;

};

#endif /* GOAL_STOPPED_H_ */

