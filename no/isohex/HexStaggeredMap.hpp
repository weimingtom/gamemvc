/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef ISOHEXENGINE_ISOHEX_HEXSTAGGAREDMAP_HPP
#define ISOHEXENGINE_ISOHEX_HEXSTAGGAREDMAP_HPP

#include <isohex/IsoStaggeredMap.hpp>

/**
 * @brief Hexagonal staggered map.
 */
class HexStaggeredMap: public IsoStaggeredMap
{
public:
    HexStaggeredMap( const IMouseMap& mouseMap );
    virtual ~HexStaggeredMap();

    virtual gcn::Point move( const gcn::Point& fromPoint,
                              Direction screenDirection ) const;

    virtual Offset scrollerOffset() const;

private:
    HexStaggeredMap(); // Unimplemented.
    HexStaggeredMap& operator=( const HexStaggeredMap& ); // Unimplemented.

};

#endif // ISOHEXENGINE_ISOHEX_HEXSTAGGAREDMAP_HPP
