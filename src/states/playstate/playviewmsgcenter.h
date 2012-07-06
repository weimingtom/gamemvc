/*
 * PlayViewMsgCenter.h
 *
 *  Created on: 16/12/2009
 *      Author: 79481180
 */

#ifndef PLAYVIEWMSGCENTER_H_
#define PLAYVIEWMSGCENTER_H_

#include <guichan.hpp>
#include <mvc/View.h>

class PlayControllerMsgCenter;
class PlayModel;
class XmlGui;
class Interface;

class PlayViewMsgCenter: public View < PlayModel, PlayControllerMsgCenter >
{
  public:

    PlayViewMsgCenter( PlayModel* model,
                       XmlGui& xmlgui );
    void Initialize();

  private:

    const Interface& m_interface_;
    gcn::Widget* m_msgcenter;
    gcn::Rectangle m_pos; // Posicion absoluta del widget..

    void Draw();

};

#endif /* PLAYVIEWMSGCENTER_H_ */
