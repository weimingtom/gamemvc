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

#include <boost/scoped_ptr.hpp>

#include <mvc/View.h>

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
    void Initialize();

  private:

    void Draw();

    boost::scoped_ptr < XmlGui > xmlgui_;
    gcn::Widget* top_;
    gcn::TextField* text_;

};

#endif /* INTROVIEW_H_ */
