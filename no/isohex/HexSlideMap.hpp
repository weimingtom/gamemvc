/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef ISOHEXENGINE_ISOHEX_HEXSLIDEMAP_HPP
#define ISOHEXENGINE_ISOHEX_HEXSLIDEMAP_HPP

#include <isohex/IsoSlideMap.hpp>

/**
 * @brief Hexagonal slide map.
 */
class HexSlideMap: public IsoSlideMap
{
public:
    HexSlideMap( const IMouseMap& mouseMap );
    virtual ~HexSlideMap();

    virtual gcn::Point move( const gcn::Point& fromPoint,
                              Direction screenDirection ) const;

    virtual Offset scrollerOffset() const;

private:
    HexSlideMap(); // Unimplemented.
    HexSlideMap& operator=( const HexSlideMap& ); // Unimplemented.

};

#endif // ISOHEXENGINE_ISOHEX_HEXSLIDEMAP_HPP
