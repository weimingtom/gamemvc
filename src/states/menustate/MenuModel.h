/*
 * MenuModel.h
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#ifndef MENUMODEL_H_
#define MENUMODEL_H_

#include <string>

#include <misc/Interface.h>
#include <mvc/Model.h>

class MyGame;
namespace gcn {
	class Gui;
}
class Interface;

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

	MenuModel( MyGame& game );
	virtual ~MenuModel();

	bool isEnd();
	void setEnd( const MenuModel::EndTypes& type );
	MenuModel::EndTypes getEnd() const;

	void Update();

	const Interface& interface() const;

	void changeResolution( const Interface::ScreenResolutionType& res );
	const Interface::ScreenResolutionType& getResolution() const;

private:

	MyGame& m_game_;
	MenuModel::EndTypes m_endtype;
	Interface::ScreenResolutionType m_res_;

};

#endif /* MENUMODEL_H_ */
