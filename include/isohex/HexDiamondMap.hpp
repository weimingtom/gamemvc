/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef ISOHEXENGINE_ISOHEX_HEXDIAMONDMAP_HPP
#define ISOHEXENGINE_ISOHEX_HEXDIAMONDMAP_HPP

#include <isohex/IsoDiamondMap.hpp>

/**
 * @brief Hexagonal diamond map.
 */
class HexDiamondMap: public IsoDiamondMap
{
public:
    HexDiamondMap( const IMouseMap& mouseMap );
    virtual ~HexDiamondMap();

    virtual gcn::Point move( const gcn::Point& fromPoint,
                              Direction screenDirection ) const;

private:
    HexDiamondMap(); // Unimplemented.
    HexDiamondMap& operator=( const HexDiamondMap& ); // Unimplemented.

};

#endif // ISOHEXENGINE_ISOHEX_HEXDIAMONDMAP_HPP
