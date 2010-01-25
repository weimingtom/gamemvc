/*
 * IntroModel.h
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#ifndef INTROMODEL_H_
#define INTROMODEL_H_

#include <boost/thread.hpp>

#include <mvc/Model.h>
#include <misc/Interface.h>

class MyGame;
namespace gcn{

	class Gui;

}
class TiXmlElement;

class IntroModel: public Model
{
public:
	enum EndTypes
	{
		CONTINUE = -1,
		QUIT,
		MENU

	};

	IntroModel(MyGame& game);
	virtual ~IntroModel();
	void Update();

	void setEnd( const IntroModel::EndTypes& type );
	IntroModel::EndTypes getEnd() const;

	void setFinal();

	int	 getAlpha();

	const Interface::ScreenResolutionType& getResolution() const;
	gcn::Gui& Gui() const;

private:

	MyGame&                            m_game_;
	int					 			   alpha;
	bool 							   m_final;
	IntroModel::EndTypes 			   m_endtype;
	Interface::ScreenResolutionType	   m_res_;

	boost::packaged_task < int >       pt;
	boost::unique_future < int >       fi;
	boost::thread	                   thr;

	int run();
	bool LoadXML( TiXmlElement* pXMLData );

};

#endif /* INTROMODEL_H_ */
