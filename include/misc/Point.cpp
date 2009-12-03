#include "Point.h"
#include <cmath>
namespace gcn {
	//constructor
	Point::Point( int x,
					int y ) {
		//set the x and y of the point
		Set( 	x,
				y );
	}

	Point::Point( const Point& pt ) {
		//set x and y of the point
		X() = pt.GetX();
		Y() = pt.GetY();
	}

	//destructor
	Point::~Point() {
		//do nothing
	}

	//properties
	int& Point::X() {
		//return x component
		return ( m_x );
	}

	int& Point::Y() {
		//return y component
		return ( m_y );
	}

	int Point::GetX() const {
		//return x component
		return ( m_x );
	}

	int Point::GetY() const {
		//return y component
		return ( m_y );
	}

	void Point::SetX( int x ) {
		//assign new value to x component
		m_x = x;
	}

	void Point::SetY( int y ) {
		//assign new value to y component
		m_y = y;
	}

	//setter
	Point& Point::Set( 	int x,
							int y ) {
		//set x and y
		X() = x;
		Y() = y;
		//return this point
		return ( *this );
	}

	Point& Point::Copy( Point& pt ) {
		//copy x and y
		X() = pt.X();
		Y() = pt.Y();
		//return this point
		return ( *this );
	}

	//move
	Point& Point::Move( 	int dx,
							int dy ) {
		//move x and y
		X() += dx;
		Y() += dy;
		//return this point
		return ( *this );
	}

	Point& Point::Add( Point& pt ) {
		//add point to this point
		( *this ) += pt;
		//return this point
		return ( *this );
	}

	Point& Point::Subtract( Point& pt ) {
		//subtract point from this point
		( *this ) -= pt;
		//return this point
		return ( *this );
	}

	//scale
	Point& Point::Scale( int scalar ) {
		//multiply this point by a scalar
		( *this ) *= scalar;
		//return this point
		return ( *this );
	}

	//distance
	int Point::Distance( Point& pt ) {
		//calculate distance
		int distance = X() * X() + Y() * Y();
		distance = (int) sqrt( distance );
		//return the distance
		return ( distance );
	}

	//operators
	//assignment
	Point& Point::operator =( const Point& pt ) {
		//copy x and y
		X() = pt.GetX();
		Y() = pt.GetY();
		//return this point
		return ( *this );
	}

	Point& Point::operator +=( Point& pt ) {
		//add to x and y
		X() += pt.X();
		Y() += pt.Y();
		//return this point
		return ( *this );
	}

	Point& Point::operator -=( Point& pt ) {
		//subtract x and y
		X() -= pt.X();
		Y() -= pt.Y();
		//return this point
		return ( *this );
	}

	Point& Point::operator *=( int scalar ) {
		//multiply by scalar
		X() *= scalar;
		Y() *= scalar;
		//return this point
		return ( *this );
	}

	Point& Point::operator /=( int scalar ) {
		//divide by scalar
		X() /= scalar;
		//return this point
		return ( *this );
	}

	//unary
	Point Point::operator -() {
		//unary negativeness--multiply by -1
		Point pt = ( *this );
		pt *= -1;
		return ( pt );
	}

	Point Point::operator +() {
		//unary positiveness
		return ( *this );
	}

	Point Point::operator +( Point& pt ) {
		//add points together
		Point result;
		result = ( *this );
		result += pt;
		//return new point
		return ( result );
	}

	Point Point::operator -( Point& pt ) {
		//subtract points
		Point result;
		result = ( *this );
		result -= pt;
		//return new point
		return ( result );
	}

	Point Point::operator *( int scalar ) {
		//multiply point by scalar
		Point result;
		result = ( *this );
		result *= scalar;
		//return new point
		return ( result );
	}

	Point Point::operator /( int scalar ) {
		//divide by scalar
		Point result;
		result = ( *this );
		result /= scalar;
		//return new point
		return ( result );
	}

	//comparison
	bool Point::operator ==( Point& pt ) {
		//check for equality
		return ( X() == pt.X() && Y() == pt.Y() );
	}

	bool Point::operator !=( Point& pt ) {
		//check for inequality
		return ( !( ( *this ) == pt ) );
	}

	Point operator *( 	int scalar,
						Point& pt ) {
		//scalar*pt rather than pt*scalar, still the same idea...
		Point result = pt;
		result *= scalar;
		return ( result );
	}
}
