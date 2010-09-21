/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef ISOHEXENGINE_ISOHEX_MAP_HPP
#define ISOHEXENGINE_ISOHEX_MAP_HPP

#include <memory>

#include <isohex/IMap.hpp>

class IMouseMap;

/**
 * @brief Generic map.
 *
 * Implements part of IMap methods.
 */
class Map: public IMap
{
public:
    /**
     * @brief Creates a new map.
     *
     * @param[in] mouseMap Mouse map for this map.
     */
    Map( const IMouseMap& mouseMap );

    //! Destructor.
    virtual ~Map();

    const IMouseMap& mouseMap() const;

private:
    const IMouseMap& m_mouseMap_;
};

#endif // ISOHEXENGINE_ISOHEX_MAP_HPP
