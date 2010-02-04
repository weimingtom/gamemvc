/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef ISOHEXENGINE_ISOHEX_ISOSTAGGAREDMAP_HPP
#define ISOHEXENGINE_ISOHEX_ISOSTAGGAREDMAP_HPP

#include <isohex/Map.hpp>
namespace gcn{
    class Point;
}
/**
 * @brief Isometric staggered map.
 *
 * When rendered on screen, staggered maps look like this:
 *
 * @code
 * 0,0   1,0   2,0   3,0
 *    0,1   1,1   2,1   3,1
 * 0,2   1,2   2,2   3,2
 *    0,3   1,3   2,3   3,3
 * @endcode
 */
class IsoStaggeredMap: public Map
{
public:
    IsoStaggeredMap( const IMouseMap& mouseMap );
    virtual ~IsoStaggeredMap();

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
    IsoStaggeredMap(); // Unimplemented.
    IsoStaggeredMap& operator=( const IsoStaggeredMap& ); // Unimplemented.

};

#endif // ISOHEXENGINE_ISOHEX_ISOSTAGGAREDMAP_HPP
