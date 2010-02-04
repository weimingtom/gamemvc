/*
 * SquaredMap.h
 *
 *  Created on: 06/01/2010
 *      Author: uberiain
 */

#ifndef SQUAREDMAP_HPP_
#define SQUAREDMAP_HPP_

#include <isohex/Map.hpp>

class SquaredMap: public Map
{
public:

    SquaredMap( const IMouseMap& mouseMap );
    virtual ~SquaredMap();

    virtual gcn::Point plot( const gcn::Point& ptMap ) const;

    virtual gcn::Point move( const gcn::Point& fromPoint,
                             Direction direction ) const;

    virtual Offset scrollerOffset() const;


protected:

    virtual gcn::Point moveUnrestricted( const gcn::Point& fromPoint,
                                          Direction screenDirection ) const;

private:
    SquaredMap(); // Unimplemented.
    SquaredMap& operator=( const SquaredMap& ); // Unimplemented.

};

#endif /* SQUAREDMAP_HPP_ */
