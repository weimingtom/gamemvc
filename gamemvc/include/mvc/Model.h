/*
 * Model.h
 *
 *  Created on: 27-mar-2009
 *      Author: 79481180
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <set>
#include <algorithm>
#include "Observer.h"

class Model
{
public:

	void attach( Observer* s ){m_registry.insert(s);}
	void detach( Observer* s ){m_registry.erase(s);}
	virtual void notify() {

		std::for_each(m_registry.begin(),m_registry.end(),std::mem_fun(&Observer::update));

	}
private:

	std::set < Observer* > m_registry;
};

#endif /* MODEL_H_ */
