/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef ISOHEXENGINE_ISOHEX_IMAP_HPP
#define ISOHEXENGINE_ISOHEX_IMAP_HPP

#include <memory>

#include <isohex/Offset.hpp>

namespace gcn {
    class Point;
}
class IMouseMap;

/**
 * @brief Map interface.
 */
class IMap
{
public:

    enum Direction
    {
        NORTH = 0,
        NORTH_EAST,
        EAST,
        SOUTH_EAST,
        SOUTH,
        SOUTH_WEST,
        WEST,
        NORTH_WEST
    };
    //! Available map types.
    enum MapType
    {
        SQUARED_MAP_TYPE,
        ISO_SLIDE_MAP_TYPE,
        ISO_STAGGERED_MAP_TYPE,
        ISO_DIAMOND_MAP_TYPE,
        HEX_SLIDE_MAP_TYPE,
        HEX_STAGGERED_MAP_TYPE,
        HEX_DIAMOND_MAP_TYPE
    };
    //! Contructor.
    IMap() {
    }

    //! Destructor.
    virtual ~IMap() {
    }

    /**
     * @brief Converts from world coordonate into scroll coordonate.
     *
     * @param[in] worldPoint A world coordinate to be converted to
     *          a scroll coordinate.
     * @return The scroll coordinate.
     *
     * @warning To convert to a screen coordinate, you have to
     *          substract the anchor of the scroller.
     *
     * @note This is the <i>tile walker</i> from <b>Isometric Game
     *          Programming with DirectX 7.0</b>
     */
    virtual gcn::Point plot( const gcn::Point& worldPoint ) const = 0;

    /**
     * @brief Moves on the map (in the world).
     *
     * @param[in] fromPoint Original world coordinate.
     * @param[in] screenDirection Screen (as seen by the user)
     *          direction to move.
     * @return The new world coordinate, after moving from fromPoint,
     *          allong the screenDirection.
     *
     * @note This method will return the original fromPoint if the
     *          screenDirection is not allowed for the current map.
     *          For example, if the screenDirection is NORTH or
     *          SOUTH for a hexagonal map.
     *
     * @note This is the <i>tile walker</i> from <b>Isometric Game
     *          Programming with DirectX 7.0</b>
     */
    virtual gcn::Point move( const gcn::Point& fromPoint,
                             Direction screenDirection ) const = 0;

    //! Get associated mouse map.
    virtual const IMouseMap& mouseMap() const = 0;

    //! How much to offset the scroller to avoid map jagginess.
    virtual Offset scrollerOffset() const = 0;

protected:
    /**
     * @brief Should be called only from the Scroller.
     *
     * @internal
     *
     * @see move
     * @see Scroller
     *
     * @warning This method will, contrary to the move, allows movement
     *          in any direction, regardless of the map. It should
     *          be used only by the scroller.
     */
    virtual gcn::Point moveUnrestricted( const gcn::Point& fromPoint,
                                         Direction screenDirection ) const = 0;

    /**
     * Needs access to moveUnrestricted() so that
     * it can delegate its implementation.
     */
    friend class MapFactory;

    /**
     * Needs access to moveUnrestricted() so that
     * it can use it. Scroller is the only intended
     * user of this method.
     */
    friend class Scroller;
};

typedef std::auto_ptr < IMap > IMapPtrType;

#endif // ISOHEXENGINE_ISOHEX_IMAP_HPP
