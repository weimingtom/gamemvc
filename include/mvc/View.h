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
class View: public Observer
{

public:

	View( M* model ) :
		m_model( model ),
		m_controller( 0 ) {
		m_model->attach( this );
	}

	virtual ~View() {
		m_model->detach( this );
	}
	virtual void update() {
		this->draw();
	}

	virtual C* setController( C* ctrl ) {
		C* last = m_controller;
		m_controller = ctrl;
		return last;
	}

	M& Model() const {
		return *m_model;
	}
	C& Controller() const {
		return *m_controller;
	}

	/*!
	 * Interface que se ha de definir.
	 *
	 * Esta interface se ha de definir y es donde se crea el
	 * Controller asociado a esta vista. Se define este metodo
	 * ya que hasta no tener creado el objeto View no podemos crear
	 * el Controller ya que en su creacion necesita un puntero a
	 * la clase View.
	 */
	virtual void initialize() = 0;

	virtual void draw() = 0;

private:

	M* m_model;
	C* m_controller;

};

#endif /* VIEW_H_ */
