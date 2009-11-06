/*
 * Singleton.hpp
 *
 *  Created on: 10-jun-2009
 *      Author: 79481180
 */

#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_

#include <boost/utility.hpp>
#include <boost/thread/once.hpp>
#include <boost/scoped_ptr.hpp>

// Warning: If T's constructor throws, instance() will return a null reference.

	template < class T >

	class Singleton: private boost::noncopyable
	{

	public:
		static T& Instance() {
			boost::call_once( init, flag );
			return *t;
		}

	protected:
		~Singleton() {
		}
		Singleton() {
		}

	private:

		static void init() // never throws
		{
			t.reset( new T() );
		}
		static boost::scoped_ptr < T > t;
		static boost::once_flag flag;

	};

template < class T > boost::scoped_ptr < T > Singleton < T >::t( 0 );
template < class T > boost::once_flag Singleton < T >::flag = BOOST_ONCE_INIT;

#endif /* SINGLETON_HPP_ */
