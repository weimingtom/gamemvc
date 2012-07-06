#ifndef TELEGRAM_H
#define TELEGRAM_H
//------------------------------------------------------------------------
//
//  @Name:   Telegram.h
//
//  Desc:   This defines a telegram. A telegram is a data structure that
//          records information required to dispatch messages. Messages
//          are used by game agents to communicate with each other.
//
//  @Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include <iostream>
#include <math.h>
#include <luabind/luabind.hpp>
/*!
 * @brief  Estructura que define un mensaje o telegrama.
 *
 * This defines a telegram. A telegram is a data structure that
 * records information required to dispatch messages. Messages
 * are used by game agents to communicate with each other.
 */
struct Telegram {
	/*!
	 * @brief Tiempo de retraso en el envio mensaje.
	 *
	 * messages can be dispatched immediately or delayed for a specified amount
	 * of time. If a delay is necessary this field is stamped with the time
	 * the message should be dispatched.
	 */
	double DispatchTime;
	/*!
	 * @brief Identificador entidad emisora.
	 *
	 * the entity that sent this telegram
	 */
	int Sender;
	/*!
	 * @brief Identificador entidad receptora.
	 *
	 * the entity that is to receive this telegram
	 */
	int Receiver;
	/*!
	 * @brief El mensaje en si
	 *
	 * the message itself.
	 */
	int Msg;
	/*!
	 * @brief Informacion adicional del mensaje
	 *
	 * any additional information that may accompany the message
	 */
	luabind::object ExtraInfo;
	/*!
	 * @brief Creacion telegrama nulo.
	 *
	 * Creacion de un telegrama nulo, se ha de modificar ya que nunca
	 * se enviara al ser su DispatchTime -1
	 *
	 * @return telegrama nulo.
	 */
	Telegram() :
		DispatchTime(-1), Sender(-1), Receiver(-1), Msg(-1) {
	}
	/*!
	 * @brief Creacion de un telegrama
	 *
	 * @param time Tiempo retraso en enviar el mensaje
	 * @param sender Entidad enviante
	 * @param receiver Entidad receptora
	 * @param msg Tipo mensaje
	 * @param info Informacion adicional del mensaje
	 * @return telegrama creado.
	 */
	Telegram(double time, int sender, int receiver, int msg,
			luabind::object info) :
		DispatchTime(time), Sender(sender), Receiver(receiver), Msg(msg),
				ExtraInfo(info) {
	}
};
/*!
 * @var SmallestDelay
 *
 * these telegrams will be stored in a priority queue. Therefore the >
 * operator needs to be overloaded so that the PQ can sort the telegrams
 * by time priority. Note how the times must be smaller than
 * SmallestDelay apart before two Telegrams are considered unique.
 */
const double SmallestDelay = 0.25;
/*!
 *
 */
inline bool operator==(const Telegram& t1, const Telegram& t2) {
	return (fabs(t1.DispatchTime - t2.DispatchTime) < SmallestDelay)
			&& (t1.Sender == t2.Sender) && (t1.Receiver == t2.Receiver)
			&& (t1.Msg == t2.Msg);
}
/*!
 *
 * @param t1
 * @param t2
 * @return
 */
inline bool operator<(const Telegram& t1, const Telegram& t2) {
	if (t1 == t2) {
		return false;
	}

	else {
		return (t1.DispatchTime < t2.DispatchTime);
	}
}
/*!
 *
 * @param os
 * @param t
 * @return
 */
inline std::ostream& operator<<(std::ostream& os, const Telegram& t) {
	os << "time: " << t.DispatchTime << "  Sender: " << t.Sender
			<< "   Receiver: " << t.Receiver << "   Msg: " << t.Msg;

	return os;
}
/*!
 *
 * handy helper function for dereferencing the ExtraInfo field of the Telegram
 * to the required type.
 * @param p
 * @return
 */
template<class T>
inline T DereferenceToType(void* p) {
	return *(T*) (p);
}

#endif
