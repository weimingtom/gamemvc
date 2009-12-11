#include "MessageDispatcher.h"
#include "game/BaseGameEntity.h"
#include "game/EntityManager.h"
#include "Time/CrudeTimer.h"

#include <iostream>
using std::cout;

using std::set;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//------------------------------ Instance -------------------------------------

MessageDispatcher* MessageDispatcher::Instance() {
	static MessageDispatcher instance;

	return &instance;
}

//----------------------------- Dispatch ---------------------------------
//
//  see description in header
//------------------------------------------------------------------------
void MessageDispatcher::Discharge(BaseGameEntity* pReceiver,
		const Telegram& telegram) {
	if (!pReceiver->HandleMessage(telegram)) {
		//telegram could not be handled
		cout << "Message not handled **********----------*******"<< std::endl;
	}
}
/*
 * given a message, a receiver, a sender and any time delay , this function
 * routes the message to the correct agent (if no delay) or stores
 *  in the message queue to be dispatched at the correct time
 *
 */
void MessageDispatcher::DispatchMsg(double delay, int sender, int receiver,
		int msg, luabind::object ExtraInfo) {
	//get pointers to the sender and receiver
//	BaseGameEntity* pSender = EntityMgr->GetEntityFromID(sender);
	BaseGameEntity* pReceiver = EntityMgr->GetEntityFromID(receiver);

	//make sure the receiver is valid
	if (pReceiver == NULL) {
		cout << "\nWarning! No Receiver with ID of " << receiver << " found";

		return;
	}

	//create the telegram
	Telegram telegram(0, sender, receiver, msg, ExtraInfo);

	//if there is no delay, route telegram immediately
	if (delay <= 0.0f) {
		cout << "\nInstant telegram dispatched at time: "
				<< Clock->GetCurrentTime() << " by " << sender
				<< " for " << receiver << ". Msg is " << msg << "\n\n";

		//send the telegram to the recipient
		Discharge(pReceiver, telegram);
	}

	//else calculate the time when the telegram should be dispatched
	else {
		double CurrentTime = Clock->GetCurrentTime();

		telegram.DispatchTime = CurrentTime + delay;

		//and put it in the queue
		PriorityQ.insert(telegram);

		cout << "\nDelayed telegram from " << sender
				<< " recorded at time " << Clock->GetCurrentTime() << " for "
				<< receiver << ". Msg is " << msg << "\n\n";

	}
}

//---------------------- DispatchDelayedMessages -------------------------
//
//  This function dispatches any telegrams with a timestamp that has
//  expired. Any dispatched telegrams are removed from the queue
//------------------------------------------------------------------------
void MessageDispatcher::DispatchDelayedMessages() {

	//get current time
	double CurrentTime = Clock->GetCurrentTime();

	//now peek at the queue to see if any telegrams need dispatching.
	//remove all telegrams from the front of the queue that have gone
	//past their sell by date
	while (!PriorityQ.empty()
			&& (PriorityQ.begin()->DispatchTime < CurrentTime)
			&& (PriorityQ.begin()->DispatchTime > 0)) {
		//read the telegram from the front of the queue
		const Telegram& telegram = *PriorityQ.begin();

		//find the recipient
		BaseGameEntity* pReceiver = EntityMgr->GetEntityFromID(
				telegram.Receiver);

		cout << "\nQueued telegram ready for dispatch: Sent to "
				<< pReceiver->ID() << ". Msg is " << telegram.Msg << "\n\n";

		//send the telegram to the recipient
		Discharge(pReceiver, telegram);

		//remove it from the queue
		PriorityQ.erase(PriorityQ.begin());
	}
}

