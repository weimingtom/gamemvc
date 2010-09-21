/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */

#ifndef MOUSEMAP_HPP
#define MOUSEMAP_HPP

#include <vector>
#include <memory>

#include <guichan/image.hpp>

#include <IsoHex/IMouseMap.hpp>

/**
 * @brief Mousemap interface.
 *
 * @note We derive the MouseMap from Canvas so that we can get
 *       get easy access to the underlying raw data. However
 *       we don't need the Canvas interface outside the class.
 *       Therefore, we inherit protected from Canvas.
 */
class MouseMap : public IMouseMap {
public:

	//! Constructor.
	MouseMap(const std::string& fileName );

	//! Destructor.
	virtual ~MouseMap();

	/**
	 * @brief Compute tile location based on the fine screen position.
	 */
	virtual Location computeLocation(const gcn::Point& fineScreenPosition) const;

	virtual int w() const;

	virtual int h() const;

private:

	std::auto_ptr<gcn::Image> m_surface_;
	//! Stores locations for fast computing of the mouse location.
	std::vector<Location> m_data_;

	//! Fills m_data with mouse locations. Called in the constructor.
	void init();

	MouseMap(); // Unimplemented.
	MouseMap& operator=(const MouseMap&); // Unimplemented.

};

#endif // MOUSEMAP_HPP
