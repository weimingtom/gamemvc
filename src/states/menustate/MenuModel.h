/*
 * MenuModel.h
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#ifndef MENUMODEL_H_
#define MENUMODEL_H_

#include "mvc/Model.h"

class MenuModel: public Model
{
public:

	enum EndTypes
	{
		CONTINUE = -1,
		QUIT,
		PLAY
	};

	MenuModel();
	virtual ~MenuModel();

	bool isEnd();
	void setEnd( const MenuModel::EndTypes& type );
	MenuModel::EndTypes getEnd() const;

	void Update();

private:

	MenuModel::EndTypes m_endtype;

};

#endif /* MENUMODEL_H_ */
