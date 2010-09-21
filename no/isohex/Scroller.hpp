/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef ISOENGINE_LIBISOHEX_SCROLLER_HPP
#define ISOENGINE_LIBISOHEX_SCROLLER_HPP

#include <string>
#include <ostream>
#include <memory>

#include <guichan/Rectangle.hpp>
#include <guichan/Point.hpp>

#include <isohex/IMap.hpp>

class IMouseMap;
class Offset;

/**
 * @brief World scroller.
 */
class Scroller
{
public:
    /**
     * @brief Scroll iterator.
     *
     * Can be used to plot only a reduced number of tiles, instead of
     * plotting the whole world.
     */
    class iterator
    {
    public:
        iterator();
        iterator( const iterator& it );

        ~iterator();

        iterator& operator =( const iterator& it );

        iterator& operator++();

        bool operator !=( const iterator& it ) const;
        bool operator ==( const iterator& it ) const;

        gcn::Point& operator*();
        gcn::Point* operator->();

        /**
         * @brief Checks if an iterator can be used.
         *
         * @return true if the iterator is still valid.
         * @return false if the iterator has not been yet
         *         initialized or if the iteration passed
         *         over the last element of the iteration
         *         (past the end of the iteration).
         */
        bool isValid() const;

        /**
         * @brief Returns the details of the iterator.
         *
         * @note Good for debugging.
         */
        std::string toString() const;

    private:
        static const int NE_CORNER = 0;
        static const int SE_CORNER = 1;
        static const int NW_CORNER = 2;
        static const int SW_CORNER = 3;

        //! Total number of corners.
        static const int CORNER_NO = 4;

        //! Iterated scroller.
        const Scroller* m_scroller_;

        //! Current row.
        int m_row_;

        //! Current coordinate.
        gcn::Point m_point_;

        //! Corners defining the rendered area.
        gcn::Point m_corners_[CORNER_NO];

        //! Tests if the current point is on the map.
        bool isOnMap();

        //! Helper method that copies all corners.
        void copyCorners( const iterator& it );

        //! Needed to set m_scroller_, m_corners_ and m_point_.
        friend class Scroller;

        //! Needed for testing only.
        friend class TestIsoSlideScroller;
    };

    // LIFETIME

    /**
     * @brief Constructor.
     *
     * @param [in] map Map object used to navigate the world.
     * @param [in] mapSize Map (game world) size.
     * @param [in] outputRectangle Screen rectangle used for
     *          rendering (nothing should be plotted outside it).
     * @param [in] tileAnchor Ground tile anchor.
     *
     * @warning The width and height of the mapSize should not be
     *          extremely big, or the scroller will start giving
     *          errors because of how data is stored. For example,
     *          consider that a map of 200x400 tiles, with 64x32
     *          sized tiles will need a scroller of at least
     *          12800x12800 pixels. If the screen resolutions is
     *          1280x1024, the virtual space will be arround 10x12
     *          screens (huge).
     */
    Scroller( const IMap& map,
              const gcn::Rectangle& mapSize,
              const gcn::Rectangle& outputRectangle,
              const gcn::Point& tileAnchor,
              const int& iPadding );

    //! Destructor.
    virtual ~Scroller();

    // OPERATIONS

    /**
     * @brief Centers the map.
     *
     * If possible, scroll the map so that centerPoint is in
     * the center of the viewport.
     *
     * If the point is too close to one borders, nothing will be
     * changed for the orthogonal axis. For example, if centerPoint
     * is too close to the left border, no centering will be done on
     * the x axis. However, if possible, the centering will be done
     * on the y axis.
     *
     * @param [in] screenPoint Point that should be centered.
     */
    void center( const gcn::Point& screenPoint );

    /**
     * @brief Scrolls the map.
     *
     * @param [in] screenExtent How many pixels to scroll.
     * @param [in] screenDirection Screen (user) direction to scroll in.
     */
    void scroll( int screenExtent,
                 IMap::Direction screenDirection );

    /**
     * @brief Converts a screen coordinate to a map (world) coordinate.
     *
     * @param screenPoint Screen coordinate to convert.
     * @return Coordinate of the world tile that contains the screenPoint.
     */
    gcn::Point map( const gcn::Point& screenPoint ) const;

    /**
     * @brief Get a screen iterator.
     *
     * @return A screen iterator object.
     */
    iterator begin() const;

    /**
     * @brief Get a screen iterator.
     *
     * @param[in] offset Offset (in pixels) relatively to the
     *          m_outputRectangle_.
     * @return A screen iterator object.
     */
    iterator begin( const Offset& offset ) const;

    /**
     * @brief Get a screen iterator over a section of the output.
     *
     * @param[in] rectangle Target rectangle. Normally, it should
     *           be a rectangle contained by the m_anchorRectangle_.
     *           However, there is no explicit check to enforces this.
     * @param[in] offset Offset (in pixels) relatively to the
     *          m_outputRectangle_.
     * @return A screen iterator object.
     */
    iterator begin( const gcn::Rectangle& rectangle,
                    const Offset& offset ) const;

    /**
     * @brief Get a screen iterator over a section of the output.
     *
     * @param[in] rectangle Target rectangle. Normally, it should
     *           be a rectangle contained by the m_anchorRectangle_.
     *           However, there is no explicit check to enforces this.
     * @return A screen iterator object.
     */
    iterator begin( const gcn::Rectangle& rectangle ) const;

    //! Returns the element past the last element of an iteration.
    iterator end() const;

    /**
     * @brief Converts from world coordonate into scroll coordonate.
     *
     * This method is like IMap::plot, but adjusts for the
     * scroller's anchor and for the offset of the output rectangle.
     *
     * It uses the associated IMap object to do most of the job.
     *
     * @see IMap::plot.
     */
    gcn::Point plot( const gcn::Point& worldPoint ) const;

    /**
     * @brief Moves on the map (in the world).
     *
     * Exposes IMap::move so that all operations of the associated
     * map can be done from the Scroller.
     *
     * @see IMap::move.
     */
    gcn::Point move( const gcn::Point& fromPoint,
                      IMap::Direction screenDirection ) const;

    // ACCESSORS

    /**
     * @brief Returns the map (world) rectangle.
     */
    const gcn::Rectangle& mapSize() const;

    /**
     * @brief Returns the scroller anchor point.
     */
    const gcn::Point& anchor() const;

    /**
     * @brief Returns the scroller output region.
     */
    const gcn::Rectangle& outputRectangle() const;

    /**
     * @brief Get associated mouse map.
     */
    const IMouseMap& mouseMap() const;

    /**
     * @brief Get the anchor of the tiles.
     */
    const gcn::Point& tileAnchor() const;

private:
    //! Map object used.
    const IMap& m_map_;

    /**
     * @brief Mouse map object used.
     *
     * Extracted from m_map_ for more convenient access.
     */
    const IMouseMap& m_mouseMap_;

    //! Map (world) size.
    const gcn::Rectangle m_mapSize_;

    //! Output rectangle.
    const gcn::Rectangle m_outputRectangle_;

    /**
     * @brief Output rectangle offset.
     *
     * Extracted from m_outputRectangle_ for more convenient access.
     */
    const gcn::Point m_outputOffset_;

    /**
     * @brief Ground tile anchor.
     *
     * This is the anchor of the tiles used to create the ground
     * (the lowest plane).
     */
    const gcn::Point m_tileAnchor_;

    //! Viewport anchor.
    gcn::Point m_anchor_;

    //! Anchor valid space.
    gcn::Rectangle m_anchorRectangle_;

    /**
     * @brief Computes all corners that border a screen region.
     *
     * Used by the begin() methods to compute the area that is
     * going to be covered. It will call computeCoarseCorner()
     * for each of the four corners.
     *
     * @param[in/out] i Iterator that will be used.
     * @param[in] rectangle Area to traverse.
     */
    void computeCorners( iterator& i,
                         const gcn::Rectangle& rectangle ) const;

    /**
     * @brief Computes a coarse corner of the iterator.
     */
    gcn::Point computeCoarseCorner( const gcn::Point& corner ) const;
};

typedef std::auto_ptr < Scroller > ScrollerPtrType;

std::ostream& operator <<( std::ostream& os,
                           const Scroller::iterator& it );

#endif // ISOENGINE_LIBISOHEX_SCROLLER_HPP
