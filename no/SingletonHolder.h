/*
 * SingletonHolder.h
 *
 *  Created on: 08-jun-2009
 *      Author: 79481180
 */

#ifndef SINGLETONHOLDER_H_
#define SINGLETONHOLDER_H_

template < class T > struct CreateLeaking
{

	// Se crea un puntero a la clase T cuando se llama
	// por primera vez a Instance dentro de la clase SingletonHolder.
	// No se borra implicitamente, luego se produce un leak de memoria
	// si no lo borramos explicitamente mediante:
	// delete &SingletonHolder< T , CreateLeaking >::Instance()
	// siendo T la clase a la cual la queremos hacer Singleton

	static T* Create() {
		return new T;
	}

};

template < class T > struct CreateMeyers
{

	// Se crea una instancia cuando se llama por primera vez
	// a Instance dentro de la clase SingletonHolder
	// y se borra al final de la ejecución del programa.

	static T* Create() {

		static T _instance;

		return &_instance;

	}

};

template < class T, template < class > class CreationPolicy = CreateMeyers >

class SingletonHolder
{

public:

	static T& Instance() {

		if ( !m_pInstance ) m_pInstance = CreationPolicy < T >::Create();

		return *m_pInstance;

	}

private:

	SingletonHolder(); // hidden, prevent creating instances of SingletonHolder
	~SingletonHolder();
	SingletonHolder( SingletonHolder const& ); // hidden
	SingletonHolder& operator=( SingletonHolder const& ); // hidden

	static T* m_pInstance;

};

template < class T, template < class > class C >
T* SingletonHolder < T, C >::m_pInstance = 0;

#endif /* SINGLETONHOLDER_H_ */
