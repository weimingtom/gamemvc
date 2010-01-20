/*
 * MenuModel.h
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#ifndef MENUMODEL_H_
#define MENUMODEL_H_

#include <string>

#include "mvc/Model.h"

class MyGame;

class MenuModel: public Model
{
public:

	enum EndTypes
	{
		CONTINUE = -1,
		QUIT,
		PLAY,
		CHANGERESOLUTION,
	};

	MenuModel(MyGame& game);
	virtual ~MenuModel();

	bool isEnd();
	void setEnd( const MenuModel::EndTypes& type );
	MenuModel::EndTypes getEnd() const;

	void Update();

	void changeResolution(const std::pair < std::string, bool >& res );
	const std::pair<std::string,bool>& getResolution() const;
	int getPosResolution();

	MyGame& game();

private:

	MyGame&						m_game_;
	MenuModel::EndTypes 		m_endtype;
	std::pair<std::string,bool>	m_res_;

};

#endif /* MENUMODEL_H_ */
