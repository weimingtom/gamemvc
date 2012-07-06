/*
 * View.h
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#ifndef VIEW_H_
#define VIEW_H_

#include "Observer.h"

template < typename M, typename C >
class View : public Observer
{

  public:

    View( M* model )
        : model_( model ),
          controller_( 0 )
    {
      model_->Attach( this );
    }

    virtual ~View()
    {
      model_->Detach( this );
    }
    void Update()
    {
      this->Draw();
    }

    virtual C* controller( C* ctrl )
    {
      C* last = controller_;
      controller_ = ctrl;
      return last;
    }

    M& model() const
    {
      return *model_;
    }
    C& controller() const
    {
      return *controller_;
    }

    /**
     * Interface que se ha de definir.
     *
     * Esta interface se ha de definir y es donde se crea el
     * Controller asociado a esta vista. Se define este metodo
     * ya que hasta no tener creado el objeto View no podemos crear
     * el Controller ya que en su creacion necesita un puntero a
     * la clase View.
     */
    virtual void Initialize() = 0;

  private:

    /**
     * Dibujar el view
     */
    virtual void Draw() = 0;

    M* model_;
    C* controller_;

};

#endif /* VIEW_H_ */
