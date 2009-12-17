/*
 * Model.h
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
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

	void attach( Observer* s ) {
		m_registry.push_back( s ); // Para mantener el orden de insercion...
	}
	void detach( Observer* s ) {
		m_registry.erase( 	std::remove( 	m_registry.begin(),
											m_registry.end(),
											s ),
							m_registry.end() );

	}
	virtual void notify() {

		std::for_each( 	m_registry.begin(),
						m_registry.end(),
						std::mem_fun( &Observer::update ) );

	}
private:

	std::vector < Observer* > m_registry;
};

#endif /* MODEL_H_ */
