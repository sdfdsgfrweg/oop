// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "rectangle.hpp"

#include <stdexcept>

/*****************************************************************************/


/*****************************************************************************/

Rectangle::Rectangle(
	const Point & _point1,
	const Point & _point2
)
	: m_leftUp(_point1)
	, m_rightDown(_point2)
{
	if (m_leftUp.m_x > m_rightDown.m_x ||
		m_leftUp.m_y > m_rightDown.m_y)
		throw std::logic_error("Invalid rectangle coordinates");

	m_heigth = m_rightDown.m_y - m_leftUp.m_y;
	m_width = m_rightDown.m_x - m_leftUp.m_x;
}

Rectangle::Rectangle(
	const Point & _point1,
	int _width,
	int _height
)
	: m_leftUp(_point1)
	, m_heigth(_height)
	, m_width(_width)
{
	if (_height < 1 || _width < 1)
		throw std::logic_error("Invalid rectangle coordinates");

	m_rightDown.m_x = m_leftUp.m_x + m_width;
	m_rightDown.m_y = m_leftUp.m_y + m_heigth;
}

bool Rectangle::contains(Point _p) const
{
	return false;
}

bool Rectangle::contains(Point _p1, Point _p2) const
{
	return false;
}

bool Rectangle::intersects(const Rectangle & _r) const
{
	return false;
}

bool Rectangle::covers(const Rectangle & _r) const
{
	return false;
}
