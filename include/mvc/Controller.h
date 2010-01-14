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
class Controller: public Observer
{

public:

	Controller( V* view ) :
		m_view( view ) {
		m_model = &m_view->Model();
		m_model->attach( this );
	}
	virtual ~Controller() {
		m_model->detach( this );
	}

	virtual void update() {
	} // Default no-op.

	M& Model() const {
		return *m_model;
	}
	V& View() const {
		return *m_view;
	}
private:

	V* m_view;
	M* m_model;

};

#endif /* CONTROLLER_H_ */
