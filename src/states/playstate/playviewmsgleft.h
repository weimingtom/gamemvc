/*
 * PlayViewMsgLeft.h
 *
 *  Created on: 16/12/2009
 *      Author: 79481180
 */

#ifndef PLAYVIEWMSGLEFT_H_
#define PLAYVIEWMSGLEFT_H_

#include <guichan.hpp>
#include <mvc/View.h>

class PlayControllerMsgLeft;
class PlayModel;
class PlayView;
class XmlGui;

class PlayViewMsgLeft: public View < PlayModel, PlayControllerMsgLeft >
{
  public:

    PlayViewMsgLeft( PlayModel* model,
                     XmlGui& xmlgui );
    void Initialize();

    void setMsgLeftname( const std::string& name );
    void setMsgLeftX( const int& X );
    void setMsgLeftY( const int& Y );
    void resetMsgLeft();

  private:

    gcn::Widget* m_msgleft;
    gcn::TextField* m_name;
    gcn::TextField* m_posX;
    gcn::TextField* m_posY;

    void Draw();

};

#endif /* PLAYVIEWMSGLEFT_H_ */
