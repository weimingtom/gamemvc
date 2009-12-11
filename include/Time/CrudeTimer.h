#ifndef CRUDETIMER_H
#define CRUDETIMER_H
//------------------------------------------------------------------------
//
//  Name:   CrudeTimer.h
//
//  Desc:   timer to measure time in seconds
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <SDL/SDL.h>

#define Clock CrudeTimer::Instance()
/*!
 *  @brief Temporizador en segundos.
 *
 *  Da el tiempo transcurrido desde la creacion de la clase
 *  hasta la llamada a la misma.
 *
 */
class CrudeTimer {

public:
	/*!
	 *
	 * @return
	 */
	static CrudeTimer* Instance();
	/*!
	 * returns how much time has elapsed since the timer was started
	 *
	 * @return
	 */
	double GetCurrentTime() {
		return (double)SDL_GetTicks()/1000.0 - dStartTime;
	}

private:

	//set to the time (in seconds) when class is instantiated
	double dStartTime;

	//set the start time
	CrudeTimer() {
		dStartTime = (double)SDL_GetTicks()/1000.0;
	}

	//copy ctor and assignment should be private
	CrudeTimer(const CrudeTimer&);
	CrudeTimer& operator=(const CrudeTimer&);

};

#endif
