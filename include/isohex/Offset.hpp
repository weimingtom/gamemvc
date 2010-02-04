/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef ISOHEXENGINE_ISOHEX_OFFSET_HPP
#define ISOHEXENGINE_ISOHEX_OFFSET_HPP

#include <ostream>

/**
 * @brief Offset of a rectangular area.
 */
class Offset
{
public:
    //! Default constructor.
    Offset();

    //! Constructor.
    Offset( int left,
            int right,
            int top,
            int bottom );

    /**
     * @brief Left offset.
     *
     * Pozitive values signifies <b>to the left</b>.
     * of the current left margin
     */
    int m_left;

    /**
     * @brief Right offset.
     *
     * Pozitive values signifies <b>to the right</b>
     * of the current right margin.
     */
    int m_right;

    /**
     * @brief Top offset.
     *
     * Pozitive values signifies <b>above</b>
     * the current top margin.
     */
    int m_top;

    /**
     * @brief Bottom offset.
     *
     * Pozitive values signifies <b>below</b>
     * the current bottom margin.
     */
    int m_bottom;
};

std::ostream& operator <<( std::ostream& os,
                           const Offset& offset );

#endif // ISOHEXENGINE_ISOHEX_OFFSET_HPP
