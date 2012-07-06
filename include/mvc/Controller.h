/*
 * Controller.h
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Observer.h"
#include "View.h"
#include "Model.h"

template < typename M, typename V >
class Controller
{

  public:

    Controller( V* view )
        : view_( view ),
          model_( &view->model() )
    {
    }

    virtual ~Controller()
    {
    }

    M& model() const
    {
      return *model_;
    }

    V& view() const
    {
      return *view_;
    }

  private:

    V* view_;
    M* model_;

};

#endif /* CONTROLLER_H_ */
