// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "numeric_range.hpp"

#include <stdexcept>

/*****************************************************************************/

NumericRange::Iterator::Iterator(int _position)
	: m_currentPosition(_position)
{}

/*****************************************************************************/

int NumericRange::Iterator::operator*() const
{
	return m_currentPosition;
}

/*****************************************************************************/

bool NumericRange::Iterator::operator==(Iterator i) const
{
	return i.m_currentPosition == m_currentPosition;
}

/*****************************************************************************/

bool NumericRange::Iterator::operator!=(Iterator i) const
{
	return !(i == *this);
}

/*****************************************************************************/

NumericRange::Iterator & NumericRange::Iterator::operator++()
{
	NumericRange::Iterator copy = *this;

	m_currentPosition++;

	return copy;
}

/*****************************************************************************/

NumericRange::Iterator NumericRange::Iterator::operator++(int)
{
	m_currentPosition++;

	return * this;
}

/*****************************************************************************/

NumericRange::NumericRange()
	: m_highBound(0)
	, m_lowBound(0)
{}

/*****************************************************************************/

NumericRange::NumericRange(int _low, int _high)
	: m_lowBound(_low)
	, m_highBound(_high)
{
	if (m_lowBound > m_highBound)
		throw std::logic_error("Low bound higher than high bound");
}

/*****************************************************************************/

NumericRange::NumericRange(std::string const & _str)
{
	std::string lhs, rhs;

	if (_str.find("[") == std::string::npos) throw std::logic_error("Invalid format");

	if (_str.find("]") == std::string::npos) throw std::logic_error("Invalid format");
	
	if (_str.find(":") == std::string::npos) throw std::logic_error("Invalid format");

	int leftBracket = 0, rightBracket = 0, colon = 0;
	for (int i = 0; i < _str.length(); i++)
	{
		if (_str[i] == '[') leftBracket++;
		if (_str[i] == ']') rightBracket++;
		if (_str[i] == ':') colon++;
	}

	if (leftBracket > 1 || rightBracket > 1 || colon > 1) throw std::logic_error("Invalid format");

	bool isDivided = false;
	for (int i = 1; i < _str.length() - 1; i++)
	{
		if (_str[i] == ':')
		{
			isDivided = true;
			continue;
		}
		(isDivided) ? rhs += _str[i] : lhs += _str[i];
	}

	if (!std::atoi(lhs.c_str())) throw std::logic_error("Invalid format");

	if (!std::atoi(rhs.c_str())) throw std::logic_error("Invalid format");

	m_lowBound = std::atoi(lhs.c_str());
	m_highBound = std::atoi(rhs.c_str());

	if (m_lowBound > m_highBound)
		throw std::logic_error("Low bound higher than high bound");
}

/*****************************************************************************/

std::ostream & operator<<(std::ostream & _s, NumericRange const & _nr)
{
	_s << "[" << _nr.getLowBound() << ":" << _nr.getHighBound() << "]";
	return _s;
}

/*****************************************************************************/