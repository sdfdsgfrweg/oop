// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "rational_number.hpp"

#include <stdexcept>

/*****************************************************************************/

RationalNumber::RationalNumber(
	int _numerator,
	int _denumerator
)
{
	if (_denumerator == 0)
		throw std::logic_error("Zero denominator");


	bool isNegative = false;
	
	if (_denumerator < 0 || _numerator < 0) isNegative = true;
	if (_denumerator < 0 && _numerator < 0) isNegative = false;

	m_numerator = std::abs(_numerator);
	m_denominator = std::abs(_denumerator);

	simplifing();

	if (isNegative) m_numerator = -m_numerator;
}


/*****************************************************************************/

void RationalNumber::simplifing()
{
	int max = 1;
	for (int i = 1; i < m_numerator; i++)
		if (m_numerator % i == 0 && m_denominator % i == 0 && i > max) max = i;

	while (true)
	{
		if (m_denominator / max || m_numerator / max) break;
		m_numerator /= max;
		m_denominator /= max;
	}
}

bool RationalNumber::operator == (const RationalNumber & _rhs)
{
	return m_numerator == _rhs.m_numerator && m_denominator == _rhs.m_denominator;
}

bool RationalNumber::operator != (const RationalNumber & _rhs)
{
	return !(*this == _rhs);
}

bool RationalNumber::operator >= (const RationalNumber & _rhs)
{
	double lhs = m_numerator / m_denominator;
	double rhs = _rhs.m_numerator / _rhs.m_denominator;

	return lhs >= rhs;
}

bool RationalNumber::operator <= (const RationalNumber & _rhs) 
{
	double lhs = m_numerator / m_denominator;
	double rhs = _rhs.m_numerator / _rhs.m_denominator;

	return lhs <= rhs;
}

bool RationalNumber::operator > (const RationalNumber & _rhs)
{
	double lhs = m_numerator / m_denominator;
	double rhs = _rhs.m_numerator / _rhs.m_denominator;

	return lhs > rhs;
}

bool RationalNumber::operator < (const RationalNumber & _rhs)
{
	double lhs = m_numerator / m_denominator;
	double rhs = _rhs.m_numerator / _rhs.m_denominator;

	return lhs < rhs;
}

void RationalNumber::operator *= (const RationalNumber & _rhs)
{

}

RationalNumber RationalNumber::operator * (const RationalNumber & _rhs)
{
	return RationalNumber(0, 1);
}

RationalNumber RationalNumber::operator + (const RationalNumber & _rhs)
{

	return RationalNumber(0, 1);
}

void RationalNumber::operator += (const RationalNumber & _rhs)
{

}

void RationalNumber::operator -= (const RationalNumber & _rhs)
{

}

RationalNumber RationalNumber::operator - (const RationalNumber & _rhs)
{

	return RationalNumber(0, 1);
}

RationalNumber RationalNumber::operator / (const RationalNumber & _rhs)
{

	return RationalNumber(0, 1);
}

void RationalNumber::operator /= (const RationalNumber & _rhs)
{

}