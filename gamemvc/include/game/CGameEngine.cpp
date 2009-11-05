#include "CGameEngine.h"

#include <iostream>
#include <tinyxml.h>
#include <misc/log.h>

void CGameEngine::Init() {

	m_running = true;
	LAPP_ << "CGameEngine Init";
}

void CGameEngine::Cleanup() {
	// cleanup the all states
	while ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}
	LAPP_ << "CGameEngine Cleanup";
}

void CGameEngine::ChangeState( CGameState * state ) {
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}
	// store and init the new state
	states.push_back( state );
	states.back()->Init();
}

void CGameEngine::PushState( CGameState * state ) {
	// pause current state
	if ( !states.empty() ) {
		states.back()->Pause();
	}
	// store and init the new state
	states.push_back( state );
	states.back()->Init();
}

void CGameEngine::PopState() {
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}
	// resume previous state
	if ( !states.empty() ) {
		states.back()->Resume();
	}
}
void CGameEngine::HandleEvents() {
	// let the state handle events
	states.back()->HandleEvents();
}
void CGameEngine::Update() {
	// let the state update the game
	states.back()->Update();
}
void CGameEngine::Draw() {
	// let the state draw the screen
	states.back()->Draw();
}
