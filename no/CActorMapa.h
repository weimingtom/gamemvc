/*
 * CActorMapa.h
 *
 *  Created on: 14-ago-2008
 *      Author: 79481180
 */

#ifndef CACTORMAPA_H_
#define CACTORMAPA_H_

#include <string>
using namespace std;

#include <boost/shared_ptr.hpp>

#include <SDL++/Point.h>

#include "misc/Smoother.h"

#include "game/MovingEntity.h"
#include <Goals/Goal.h>

class GameWorld;
class Vector2D;
class CActorType;
class CActor_PathPlanner;
class Goal_Think;
class SteeringBehavior;
class CCanvas;
class ModifierGoalActor;

class CActorMapa: public MovingEntity
{
public:

	enum message_type
	{
		Msg_Blank = 1,
		Msg_PathReady,
		Msg_NoPathAvailable,
		Msg_Goto

	};

	/*!
	 *
	 * @param elGameWorld
	 * @param laPosicion
	 * @param elActorTipo
	 * @return
	 */
	CActorMapa( GameWorld* elGameWorld,
				Vector2D laPosicion,
				CActorType* elActorTipo );
	virtual ~CActorMapa();
	//-------------------------------------------accessor methods

	GameWorld* const World() const {
		return m_pWorld;
	}

	Vector2D SmoothedHeading() const {
		return m_vSmoothedHeading;
	}

	void SmoothingOff() {
		m_bSmoothingOn = false;
	}
	void SmoothingOn() {
		m_bSmoothingOn = true;
	}
	void ToggleSmoothing() {
		m_bSmoothingOn = !m_bSmoothingOn;
	}
	bool isSmoothingOn() const {
		return m_bSmoothingOn;
	}
	string GetPersonality() const {
		return m_Personality;
	}
	void SetPersonality( string personality ) {
		m_Personality = personality;
	}
	string GetState() const {
		return m_State;
	}
	;
	void SetState( string elState ) {
		m_State = elState;
	}
	;

	string GetDir() const {
		return m_Dir;
	}
	;
	void SetDir( string laDir ) {
		m_Dir = laDir;
	}
	;

	int GetFrame() const {
		return m_iFrame;
	}
	;
	void SetFrame( int iFrame ) {
		m_iFrame = iFrame;
	}
	;
	int GetMaxFrames() const;

	int GetTimeElapsed() const {
		return m_iTimeElapsed;
	}
	;
	void SetTimeElapsed( int iTimeElapsed ) {
		m_iTimeElapsed = iTimeElapsed;
	}
	;

	void Update( long iElapsedTicks );
	virtual bool HandleMessage( const Telegram& msg );
	void Draw( 	CCanvas* pDestSurface,
				CPoint point );
	void Render();

	bool isAtPosition( Vector2D pos ) const;
	string isHeadingAt();

	void PonSelect() {
		m_bSelect = true;
	}

	void QuitaSelect() {
		m_bSelect = false;
	}

	long GetLastTimeElapsed() const {
		return m_LastTimeElapsed;
	}
	void SetLastTimeElapsed( long val ) {
		m_LastTimeElapsed = val;
	}
	;

	CActor_PathPlanner* const GetPathPlanner() {
		return m_pPathPlanner;
	}

	//returns a value indicating the time in seconds it will take the bot
	//to reach the given position at its current speed.
	double CalculateTimeToReachPosition( Vector2D pos ) const;

	//similar to above. Returns true if the bot can move between the two
	//given positions without bumping into any walls
	bool canWalkBetween( 	Vector2D from,
							Vector2D to ) const;
	bool isPossessed() {
		return true;
	}
	Goal_Think* GetBrain() const {
		return m_pBrain;
	}

	void SetBrain( Goal_Think* brain );

	SteeringBehavior* const Steering() const {
		return m_pSteering;
	}
	double TimeElapsed() const {
		return m_dTimeElapsed;
	}
	virtual void UpdateFrame( long iElapsedTicks ); //! Puede ser usado en Lua.

	ModifierGoalActor*	GetModifierGoal(){
		return m_pModifierGoal;
	}

private:
	//a pointer to the world data. So a vehicle can access any obstacle,
	//path, wall or agent data
	GameWorld* m_pWorld;

	CActorType* m_elActorTipo; //! Puntero al tipo de actor que estamos tratando.

	string m_Personality;
	string m_State; //! Estado tabla de bmp.
	string m_Dir; //! Direccion en la tabla de bmp.
	int m_iFrame;
	int m_iTimeElapsed;
	long m_LastTimeElapsed; //! Tiempo desde ultima actualizacion.
	bool m_bSelect; //! Actor seleccionado.
	long m_lTotalTick; //! Para calcular el frame....

	ModifierGoalActor*	m_pModifierGoal;

	//keeps a track of the most recent update time. (some of the
	//steering behaviors make use of this - see Wander)
	double m_dTimeElapsed;

	void UpdateMovement( double time_elapsed );

	//the steering behavior class
	SteeringBehavior* m_pSteering;

	//when true, smoothing is active
	bool m_bSmoothingOn;

	//some steering behaviors give jerky looking movement. The
	//following members are used to smooth the vehicle's heading
	Smoother < Vector2D >* m_pHeadingSmoother;

	//this vector represents the average of the vehicle's heading
	//vector smoothed over the last few frames
	Vector2D m_vSmoothedHeading;

	//buffer for the vehicle shape
	std::vector < Vector2D > m_vecVehicleVB;
	void InitializeBuffer();

	//the bot uses this to plan paths
	CActor_PathPlanner* m_pPathPlanner;

	//this object handles the arbitration and processing of high level goals
	Goal_Think* m_pBrain;

	CActorMapa( const CActorMapa& actor );
	CActorMapa& operator=( const CActorMapa& actor );

};

//used for outputting debug info
inline std::string MessageToString( CActorMapa::message_type msg ) {

	switch ( msg ) {

		case CActorMapa::Msg_PathReady:
			return "Msg_PathReady";

		case CActorMapa::Msg_NoPathAvailable:
			return "Msg_NoPathAvailable";

		default:
			return "Undefined message!";

	}
}

#endif /* CACTORMAPA_H_ */
