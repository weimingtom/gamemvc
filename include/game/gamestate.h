#ifndef GAMESTATE_H
#define GAMESTATE_H

class CGameEngine;

class CGameState
{
public:

	virtual void Init(CGameEngine* game ) = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	CGameState() {
	}

};

#endif
