/*
 * PlayView.h
 *
 *  Created on: 29/10/2009
 *      Author: 79481180
 */

#ifndef PLAYVIEW_H_
#define PLAYVIEW_H_

#include <memory>
#include <string>
#include <vector>

#include <boost/scoped_ptr.hpp>
#include <guichan.hpp>

#include <mvc/View.h>

class PlayModel;
class PlayController;
class PlayViewZone;
class PlayViewMsgLeft;
class PlayViewMsgCenter;

class XmlGui;

class PlayView: public View < PlayModel, PlayController >
{
  public:

    PlayView( PlayModel* model );
    virtual ~PlayView();

    void Initialize();
    void Draw();

    void setMouse( const std::string& name,
                   const int& X,
                   const int& Y ) const;
    void resetMouse() const;

  private:

    boost::scoped_ptr < XmlGui > xmlgui;

    gcn::Widget* top;
    boost::scoped_ptr < PlayViewZone > zoneview_;
    boost::scoped_ptr < PlayViewMsgLeft > msgleftview_;
    boost::scoped_ptr < PlayViewMsgCenter > msgcenterview_;

};

#endif /* PLAYVIEW_H_ */
