/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef ISOHEXENGINE_ISOHEX_IMOUSEMAP_HPP
#define ISOHEXENGINE_ISOHEX_IMOUSEMAP_HPP

#include <memory>
namespace gcn {

    class Point;

}
/**
 * @brief Mousemap interface.
 */
class IMouseMap
{
public:
    enum Location
    {
        INVALID,
        CENTER,
        NORTH_EAST,
        SOUTH_EAST,
        SOUTH_WEST,
        NORTH_WEST
    };

    //! Constructor.
    IMouseMap() {
    }

    //! Destructor.
    virtual ~IMouseMap() {
    }

    /**
     * @brief Compute tile location based on the fine screen position.
     */
    virtual Location
    computeLocation( const gcn::Point& fineScreenPosition ) const = 0;

    //! Get mouse map's width.
    virtual int w() const = 0;

    //! Get mouse map's height.
    virtual int h() const = 0;

private:
    IMouseMap& operator=( const IMouseMap& ); // Unimplemented.
};

typedef std::auto_ptr < IMouseMap > IMouseMapPtrType;

#endif // ISOHEXENGINE_ISOHEX_MOUSEMAP_HPP
