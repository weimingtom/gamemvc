/*
 * IntroModel.h
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#ifndef INTROMODEL_H_
#define INTROMODEL_H_

#include <mvc/Model.h>
#include <misc/CrtlThread.h>

#include "loadInitData.h"

class IntroModel: public Model
{
public:
	enum EndTypes
	{
		CONTINUE = -1,
		QUIT,
		MENU

	};

	IntroModel();
	virtual ~IntroModel();
	void Update();

	bool isEnd();
	void setEnd( const IntroModel::EndTypes& type );
	IntroModel::EndTypes getEnd() const;

	void setFinal();

	int	 getAlpha();

private:

	int					 			alpha;
	bool 							m_final;
	IntroModel::EndTypes 			m_endtype;
	CrtlThread	 					m_control;
	loadInitData 					m_loadInitData;
	boost::thread					thr;
};

#endif /* INTROMODEL_H_ */
