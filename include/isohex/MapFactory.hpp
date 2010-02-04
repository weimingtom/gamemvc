/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef ISOHEXENGINE_ISOHEX_MAPFACTORY_HPP
#define ISOHEXENGINE_ISOHEX_MAPFACTORY_HPP

#include <isohex/IMap.hpp>
namespace gcn {
    class Point;
}
class IMouseMap;

/**
 * @brief Map factory.
 */
class MapFactory: public IMap
{
public:
    MapFactory( MapType mapType,
                const IMouseMap& mouseMap );
    virtual ~MapFactory();

    virtual gcn::Point plot( const gcn::Point& worldPoint ) const;

    virtual gcn::Point move( const gcn::Point& fromPoint,
                              Direction screenDirection ) const;

    virtual const IMouseMap& mouseMap() const;

    virtual Offset scrollerOffset() const;

private:
    virtual gcn::Point moveUnrestricted( const gcn::Point& fromPoint,
                                          Direction screenDirection ) const;

    IMapPtrType m_map_;

    MapFactory(); // Unimplemented.
    MapFactory& operator=( const MapFactory& ); // Unimplemented.
};

#endif // ISOHEXENGINE_ISOHEX_MAPFACTORY_HPP
