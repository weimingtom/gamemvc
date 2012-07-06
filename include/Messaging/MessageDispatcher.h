#ifndef MESSAGE_DISPATCHER_H
#define MESSAGE_DISPATCHER_H
//------------------------------------------------------------------------
//
//  Name:   MessageDispatcher.h
//
//  Desc:   A message dispatcher. Manages messages of the type Telegram.
//          Instantiated as a singleton.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <set>
#include <iostream>

#include "Telegram.h"

class BaseGameEntity;

//to make code easier to read
const double 	SEND_MSG_IMMEDIATELY = 0.0f;
const int 		NO_ADDITIONAL_INFO = 0;
const int 	   	SENDER_ID_IRRELEVANT = -1;

//to make life easier...
#define Dispatch MessageDispatcher::Instance()
/*!
 * @brief Manejo de los mensajes
 *
 * Se utiliza par el manejo de los mensajes que se envian entre
 * las diferentes entidades definidas en el juego.
 *
 */
class MessageDispatcher {

public:

	/*!
	 * this class is a singleton
	 *
	 * @return
	 */
	static MessageDispatcher* Instance();
	/*!
	 * @brief send a message to another agent. Receiving agent is referenced by ID.
	 *
	 * given a message, a receiver, a sender and any time delay , this function
	 * routes the message to the correct agent (if no delay) or stores
     * in the message queue to be dispatched at the correct time
     *
	 * @param delay
	 * @param sender
	 * @param receiver
	 * @param msg
	 * @param ExtraInfo
	 */
	void DispatchMsg(double delay, int sender, int receiver, int msg,
			luabind::object ExtraInfo);
	/*!
	 * send out any delayed messages. This method is called each time through
	 * the main game loop.
	 */
	void DispatchDelayedMessages();

private:
	/*!
	 * a std::set is used as the container for the delayed messages
	 * because of the benefit of automatic sorting and avoidance
	 * of duplicates. Messages are sorted by their dispatch time.
	 */
	std::set<Telegram> PriorityQ;
	/*!
	 * this method is utilized by DispatchMessage or DispatchDelayedMessages.
	 * This method calls the message handling member function of the receiving
	 * entity, pReceiver, with the newly created telegram
	 * @param pReceiver
	 * @param msg
	 */
	void Discharge(BaseGameEntity* pReceiver, const Telegram& msg);

	MessageDispatcher() {}

	//copy ctor and assignment should be private
	MessageDispatcher(const MessageDispatcher&);
	MessageDispatcher& operator=(const MessageDispatcher&);
};

#endif
