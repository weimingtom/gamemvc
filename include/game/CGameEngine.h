#ifndef CGAMEENGINE_H
#define CGAMEENGINE_H

#include "gamestate.h"

#include <vector>

class TiXmlElement;

#include "gamestate.h"

class CGameEngine
{

public:

	/*!
	 * @brief Inicializacion del juego.
	 *
	 */

	void ChangeState( CGameState* state );
	void PushState( CGameState* state );
	void PopState();

	void HandleEvents();
	void Update();
	void Draw();

	bool Running() {
		return m_running;
	}
	void Quit() {
		m_running = false;
	}

protected:

	virtual void Init();
	virtual void Cleanup()=0;

private:

	// the stack of states
	std::vector < CGameState* > states;
	bool m_running;

};

#endif
