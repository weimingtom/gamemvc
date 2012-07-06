/**
 * Model.h
 *
 *  Created on: 27-mar-2009
 *      Author: Rafael Ugalde Beriain
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include <functional>
#include <algorithm>
#include "Observer.h"

class Model
{
  public:

    void Attach( Observer* s )
    {
      registry_.push_back( s ); // Para mantener el orden de insercion...
    }
    void Detach( Observer* s )
    {
      registry_.erase( std::remove( registry_.begin(),
                                    registry_.end(),
                                    s ),
                       registry_.end() );

    }
    virtual void Notify()
    {

      std::for_each( registry_.begin(),
                     registry_.end(),
                     std::mem_fun( &Observer::Update ) );

    }
  private:

    std::vector < Observer* > registry_;
};

#endif /* MODEL_H_ */
