/*
 * IntroView.h
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#ifndef INTROVIEW_H_
#define INTROVIEW_H_

#include <memory>
#include <SDL/SDL.h>

#include "mvc/View.h"

class IntroModel;
class IntroController;

class XmlGui;
namespace gcn {

	class Widget;
	class TextField;

}

class IntroView: public View < IntroModel, IntroController >
{
public:

	IntroView( IntroModel* model );
	virtual ~IntroView();
	void initialize();

	virtual void draw();

private:

	std::auto_ptr < XmlGui > xmlgui;

	gcn::Widget* top;
	gcn::TextField* text;

};

#endif /* INTROVIEW_H_ */
