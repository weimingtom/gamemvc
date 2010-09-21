/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef ISOHEXENGINE_ISOHEX_ISODIAMONDMAP_HPP
#define ISOHEXENGINE_ISOHEX_ISODIAMONDMAP_HPP

#include <isohex/Map.hpp>

/**
 * @brief Isometric diamond map.
 *
 * When rendered on screen, diamond maps look like this:
 *
 * @code
 *           0,0
 *        0,1   1,0
 *     0,2   1,1   2,0
 *  0,3   1,2   2,1   3,0
 *     1,3   2,2   3,1
 *        2,3   3,2
 *           3,3
 * @endcode
 */
class IsoDiamondMap: public Map
{
public:
    IsoDiamondMap( const IMouseMap& mouseMap );
    virtual ~IsoDiamondMap();

    virtual gcn::Point plot( const gcn::Point& worldPoint ) const;

    virtual gcn::Point move( const gcn::Point& fromPoint,
                              Direction screenDirection ) const;

    virtual Offset scrollerOffset() const;

protected:
    // We can't make this private as it is
    // needed by the hex version of this map.
    virtual gcn::Point moveUnrestricted( const gcn::Point& fromPoint,
                                          Direction screenDirection ) const;

private:

    IsoDiamondMap(); // Unimplemented.
    IsoDiamondMap& operator=( const IsoDiamondMap& ); // Unimplemented.
};

#endif // ISOHEXENGINE_ISOHEX_ISODIAMONDMAP_HPP
