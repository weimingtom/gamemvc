/*
 * CActorMapa.cpp
 *
 *  Created on: 14-ago-2008
 *      Author: 79481180
 */
#include "CActorMapa.h"

#include <cmath>
#include <luabind/luabind.hpp>

#include <states/playstate/lua/Raven_Scriptor.h>

#include "game/database/CActorType.h"
#include "game/database/CPersonality.h"
#include "game/database/CStatus.h"
#include "game/database/CDir.h"
#include "game/database/CFrame.h"
#include "2d/Vector2D.h"
#include "2d/geometry.h"

#include "misc/utils.h"

#include "navigation/PathManager.h"

#include "goals/Goal_Think.h"
#include "goals/Goal_MoveToPosition.h"
#include "goals/Goal_Wander.h"
#include "Messaging/MessageDispatcher.h"

#include "CActor_PathPlanner.h"
#include "SteeringBehaviors.h"
#include "PlayModel.h"
#include "ModifierGoalActor.h"

CActorMapa::CActorMapa(PlayModel* elPlayModel, Vector2D laPosicion,
		CActorType* elActorTipo) :
	MovingEntity(laPosicion, script->GetDouble("VehicleScale"), Vector2D(0, 0),
			script->GetDouble("MaxSpeed"),

			Vector2D(sin(RandFloat() * TwoPi), -cos(RandFloat() * TwoPi)),

			script->GetDouble("VehicleMass"),

			Vector2D(script->GetDouble("VehicleScale"), script->GetDouble(
					"VehicleScale")),

			script->GetDouble("MaxHeadTurnRate"), script->GetDouble(
					"MaxSteeringForce")), m_pWorld(elPlayModel), m_elActorTipo(
			elActorTipo), m_LastTimeElapsed(0), m_bSelect(false), m_lTotalTick(
			0), m_bSmoothingOn(false), m_vSmoothedHeading(Vector2D(0, 0)),
			m_pBrain(NULL) {

	InitializeBuffer();

	//set up the steering behavior class
	m_pSteering = new SteeringBehavior(elPlayModel, this);
	//create the navigation module
	m_pPathPlanner = new CActor_PathPlanner(this);
	//set up the smoother
	m_pHeadingSmoother = new Smoother<Vector2D> (script->GetDouble(
			"NumSamplesForSmoothing"), Vector2D(0.0, 0.0));
	m_pWorld->GetCellMapa()->AddEntity(this);
	m_pModifierGoal = new ModifierGoalActor(m_pWorld->GetCellMapa());

	//	std::cout << "[C++ActorMapa] constructor" << std::endl;
}
CActorMapa::~CActorMapa() {

	delete m_pModifierGoal;
	delete m_pBrain; // Ha sido creado en Lua !!!....
	delete m_pHeadingSmoother;
	delete m_pPathPlanner;
	delete m_pSteering;

	//	std::cout << "[C++ActorMapa] destructor" << std::endl;
}
void CActorMapa::SetBrain(Goal_Think* brain) {
	m_pBrain = brain;
}
int CActorMapa::GetMaxFrames() const {
	return m_elActorTipo->GetPersonality(m_Personality).GetStatus(m_State).GetDir(m_Dir).GetMaxFrames();
}
void CActorMapa::Update(long iElapsedTicks) {

	m_iTimeElapsed = m_iTimeElapsed + iElapsedTicks;
	double time_elapsed = (m_iTimeElapsed - m_LastTimeElapsed) / 1000.0;
	m_LastTimeElapsed = m_iTimeElapsed;

	time_elapsed = 1.0; // Ojo forzamos 1 seg.

	static_cast<Goal_Think*> (m_pBrain)->Process();

	//Calculate the steering force and update the bot's velocity and position
	UpdateMovement(time_elapsed);

	UpdateFrame(iElapsedTicks);

}
//------------------------- UpdateMovement ------------------------------------
//
//  this method is called from the update method. It calculates and applies
//  the steering force for this time-step.
//-----------------------------------------------------------------------------
void CActorMapa::UpdateMovement(double time_elapsed) {

	//update the time elapsed
	m_dTimeElapsed = time_elapsed;

	//keep a record of its old position so we can update its cell later
	//in this method
	Vector2D OldPos = Pos();

	//calculate the combined steering force
	Vector2D force = m_pSteering->Calculate();

	//if no steering force is produced decelerate the player by applying a
	//braking force
	if (m_pSteering->Force().isZero()) {
		const double BrakingRate = 0.8;
		m_vVelocity = m_vVelocity * BrakingRate;
	}

	//calculate the acceleration
	Vector2D accel = force / m_dMass;

	//update the velocity
	m_vVelocity += accel * time_elapsed;

	//make sure vehicle does not exceed maximum velocity
	m_vVelocity.Truncate(m_dMaxSpeed);

	//update the position
	m_vPos += m_vVelocity * time_elapsed;

	//if the vehicle has a non zero velocity the heading and side vectors must
	//be updated
	//update the heading if the vehicle has a non zero velocity
	if (m_vVelocity.LengthSq() > 0.000001) // 0.00000001
	{
		m_vHeading = Vec2DNormalize(m_vVelocity);
		m_vSide = m_vHeading.Perp();

	} else {

		m_vVelocity.Zero();

	}
	//treat the screen as a Rectangle
	//	WrapInside( m_vPos, m_pWorld->cxClient(), m_pWorld->cyClient() );

	m_pWorld->GetCellMapa()->UpdateEntity(this, OldPos);

	if (isSmoothingOn()) {
		m_vSmoothedHeading = m_pHeadingSmoother->Update(Heading());
	}
}

void CActorMapa::UpdateFrame(long iElapsedTicks) {

	m_lTotalTick += iElapsedTicks;
	long frames = m_elActorTipo->GetPersonality(m_Personality).GetStatus(
			m_State).GetFrames();

	m_iFrame = (m_iFrame + (m_lTotalTick / frames)) % GetMaxFrames();
	m_lTotalTick %= frames;

}

bool CActorMapa::HandleMessage(const Telegram& msg) {

	if (GetBrain()->HandleMessage(msg))
		return true;
	return false;

}

void CActorMapa::Draw(gcn::Graphics* graphics, int destX, int destY) const {

	Render(); // Dibujar el propio...
	if (script->GetBool("ShowBrain"))
		m_pBrain->Render();
	if (script->GetBool("ShowPath"))
		m_pPathPlanner->Render();

	m_elActorTipo->GetPersonality(m_Personality).GetStatus(m_State).GetDir(m_Dir).GetFrame(m_iFrame)->Draw(graphics, destX, destY);
	/*
	 if ( m_bSelect ) {

	 CRectangle rec( imagen->DstRect() );
	 rec += puntoDest;
	 rec.Y() -= 4;
	 rec.W() = imagen->GetCanvas()->GetWidth();
	 rec.H() = 3;
	 pDestSurface->FillRect( rec,
	 CColor::Green );

	 }
	 */
}

//-------------------------------- Render -------------------------------------
//-----------------------------------------------------------------------------
void CActorMapa::Render() const {
	/*
	 //a vector to hold the transformed vertices
	 static std::vector < Vector2D > m_vecVehicleVBTrans;

	 //render neighboring vehicles in different colors if requested
	 if ( m_pWorld->RenderNeighbors() ) {

	 if ( IsTagged() )
	 gdi->SetPenColor( CColor::Green );
	 else
	 gdi->SetPenColor( CColor::Blue );
	 }

	 else {
	 gdi->SetPenColor( CColor::Blue );
	 }

	 if ( isSmoothingOn() ) {
	 m_vecVehicleVBTrans = WorldTransform( 	m_vecVehicleVB,
	 Pos(),
	 SmoothedHeading(),
	 SmoothedHeading().Perp(),
	 Scale() );
	 }

	 else {
	 m_vecVehicleVBTrans = WorldTransform( 	m_vecVehicleVB,
	 Pos(),
	 Heading(),
	 Side(),
	 Scale() );

	 }

	 gdi->ClosedShapeISO( m_vecVehicleVBTrans );
	 gdi->SetPenColor( CColor::Blue );
	 // Pintemos un circulo....
	 gdi->CircleISO( m_vPos, m_dBoundingRadius );
	 //and finally the crosshair
	 gdi->LineISO( m_vPos.x - m_dBoundingRadius, m_vPos.y, m_vPos.x
	 + m_dBoundingRadius, m_vPos.y );
	 gdi->LineISO( m_vPos.x, m_vPos.y - m_dBoundingRadius, m_vPos.x, m_vPos.y
	 + m_dBoundingRadius );

	 gdi->SetPenColor( CColor::White );
	 if ( m_bSelect ) {
	 Vector2D p( Pos().x - 50, Pos().y + 8 );

	 GetBrain()->RenderAtPos( p, GoalTypeToString::Instance() );
	 }
	 */
}

//------------------------ isAtPosition ---------------------------------------
//
//  returns true if the bot is close to the given position
//-----------------------------------------------------------------------------
bool CActorMapa::isAtPosition(Vector2D pos) const {

	const double tolerance = 10.0; //! Cuanto de cerca??? 10.0
	return Vec2DDistanceSq(Pos(), pos) < tolerance * tolerance;

}
std::string CActorMapa::isHeadingAt() {

	Vector2D elHeading;
	struct TabDIR {
		double angInit;
		double angFin;
		std::string sDir;
		std::string vDir; // La direccion dada la vuelta.
	};
	//
	// El calculo con atan2 produce angulos fuera de los 180.0
	// por eso el limite en 180.1 y -180.1
	//
	const int NumDIR = 10;
	// Estan al reves el Norte es el Sur !!!!! la Y esta al reves....
	const TabDIR alDIR[NumDIR] = { { 0.0, 22.5, "E", "E" }, { 22.5, 67.5, "NE",
			"SE" }, { 67.5, 112.5, "N", "S" }, { 112.5, 157.5, "NW", "SW" }, {
			157.5, 180.1, "W", "W" }, { -22.5, 0.0, "E", "E" }, { -67.5, -22.5,
			"SE", "NE" }, { -112.5, -67.5, "S", "N" }, { -157.5, -112.5, "SW",
			"NW" }, { -180.1, -157.5, "W", "W" } };
	std::string laDIR = "*";
	std::string tdir = "*";
	if (isSmoothingOn())
		elHeading = this->SmoothedHeading();
	else
		elHeading = m_vHeading;
	double IsoDeltaX = elHeading.x - elHeading.y;
	double IsoDeltaY = (elHeading.y + elHeading.x) / 2;

	double angulo = std::atan2(IsoDeltaY, IsoDeltaX) * 180.0 / Pi;
	bool final = false;
	for (int i = 0; (i < NumDIR) && !final; i++) {
		if ((angulo > alDIR[i].angInit) && (angulo <= alDIR[i].angFin)) {
			final = true;
			laDIR = alDIR[i].vDir;
			tdir = alDIR[i].sDir;
		}
	}
	return laDIR;

}

//Returns true if the bot can move between the two
//given positions without bumping into any walls
bool CActorMapa::canWalkBetween(Vector2D from, Vector2D to) const {

	return !World()->isPathObstructed(from, to, BRadius());

}

//----------------- CalculateTimeToReachPosition ----------------------
//
//  returns a value indicating the time in seconds it will take the bot
//  to reach the given position at its current speed.
//-----------------------------------------------------------------------------
double CActorMapa::CalculateTimeToReachPosition(Vector2D pos) const {

	int FrameRate = 20; // Cual es el valor ?
	return Vec2DDistance(Pos(), pos) / (MaxSpeed() * FrameRate);

}
//----------------------------- InitializeBuffer -----------------------------
//
//  fills the vehicle's shape buffer with its vertices
//-----------------------------------------------------------------------------
void CActorMapa::InitializeBuffer() {

	const int NumVehicleVerts = 3;

	Vector2D vehicle[NumVehicleVerts] = { Vector2D(-1.0f, 0.6f), Vector2D(1.0f,
			0.0f), Vector2D(-1.0f, -0.6f) };

	//setup the vertex buffers and calculate the bounding radius
	for (int vtx = 0; vtx < NumVehicleVerts; ++vtx) {
		m_vecVehicleVB.push_back(vehicle[vtx]);
	}
}

