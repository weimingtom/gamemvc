//sentinel
#ifndef __POINT_H__
#define __POINT_H__

#include "guichan/platform.hpp"

namespace gcn {

	//point class
	class Point
	{
	private:
		//x and y
		int m_x;
		int m_y;
	public:
		//constructor
		Point( int x = 0,
				int y = 0 );
		Point( const Point& pt );

		//destructor
		virtual ~Point();

		//properties
		int& X();
		int& Y();

		int GetX() const;
		int GetY() const;
		void SetX( int x );
		void SetY( int y );

		//setter
		Point& Set( 	int x,
						int y );
		Point& Copy( Point& pt );

		//move
		Point& Move( 	int dx,
						int dy );
		Point& Add( Point& pt );
		Point& Subtract( Point& pt );

		//scale
		Point& Scale( int scalar );

		//distance
		int Distance( Point& pt );

		//operators
		//assignment
		Point& operator =( const Point& pt );
		Point& operator +=( Point& pt );
		Point& operator -=( Point& pt );
		Point& operator *=( int scalar );
		Point& operator /=( int scalar );

		//unary
		Point operator -();
		Point operator +();

		Point operator +( Point& pt );
		Point operator -( Point& pt );
		Point operator *( int scalar );
		Point operator /( int scalar );

		//comparison
		bool operator ==( Point& pt );
		bool operator !=( Point& pt );

	};

	Point operator *( 	int scalar,
						Point& pt );
}
//sentinel
#endif
