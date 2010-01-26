/*
 * MyGame.h
 *
 *  Created on: 12-mar-2009
 *      Author: 79481180
 */

#ifndef MYGAME_H_
#define MYGAME_H_

#include <string>
#include <memory>

#include <game/CGameEngine.h>

class Interface;
class Param;

class MyGame: public CGameEngine {
public:

	MyGame();
	virtual ~MyGame();

	void Init(const std::string& config);
	void Cleanup();

	Interface& interface() const;
	Param&	   param() const;

private:

	std::auto_ptr<Interface> 	m_interface_;
	std::auto_ptr<Param> 		m_param_;

	/*
	 * Procedimientos privados.
	 */
	void InitParam(const std::string& config);
	void InitInterface();
	void InitLua();

};

#endif /* MYGAME_H_ */
