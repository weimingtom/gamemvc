/*
 * Author: Ionutz Borcoman <iborco@gmail.com>, (C) 2007
 * Copyright: See COPYING file that comes with this distribution
 */


#include "Offset.hpp"

Offset::Offset()
: m_left(0)
, m_right(0)
, m_top(0)
, m_bottom(0)
{
}



Offset::Offset(int left, int right, int top, int bottom)
: m_left(left)
, m_right(right)
, m_top(top)
, m_bottom(bottom)
{
}



std::ostream& operator << (
		std::ostream& os,
		const Offset& offset
		)
{
	os << "Offset("
			<< "left: " << offset.m_left
			<< ", right: " << offset.m_right
			<< ", top: " << offset.m_top
			<< ", bottom: " << offset.m_bottom
			<< ")";

	return os;
}
