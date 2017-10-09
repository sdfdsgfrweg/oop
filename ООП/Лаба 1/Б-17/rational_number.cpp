// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "rational_number.hpp"

#include <stdexcept>

/*****************************************************************************/

int RationalNumber::greatest(int _lhs, int _rhs)
{
	if (_lhs == _rhs) return _lhs;

	int greatest = _lhs * _rhs;
	int min = 0;
	for (int i = greatest; i >= 1; i--)
		if (i % _lhs == 0 && i % _rhs == 0) min = i;
	return min;
}

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
	int min = 1;
	
	for (int i = 1; i < m_numerator + 1; i++)
		if (m_numerator % i == 0 && m_denominator % i == 0 && i != 1) min = i;
	
 	while (m_numerator % min == 0 && m_denominator % min == 0)
	{
		if (min == 1) return;
		m_numerator /= min;
		m_denominator /= min;
	}
}

/*****************************************************************************/

bool RationalNumber::operator == (const RationalNumber & _rhs)
{
	return m_numerator == _rhs.m_numerator && m_denominator == _rhs.m_denominator;
}

/*****************************************************************************/

bool RationalNumber::operator != (const RationalNumber & _rhs)
{
	return !(*this == _rhs);
}

/*****************************************************************************/

bool RationalNumber::operator >= (const RationalNumber & _rhs)
{
	double lhs = (double) *this;
	double rhs = (double)_rhs;

	return lhs >= rhs;
}

/*****************************************************************************/

bool RationalNumber::operator <= (const RationalNumber & _rhs) 
{
	double lhs = (double) *this;
	double rhs = (double)_rhs;

	return lhs <= rhs;
}

/*****************************************************************************/

bool RationalNumber::operator > (const RationalNumber & _rhs)
{
	double lhs = (double) *this;
	double rhs = (double)_rhs;

	return lhs > rhs;
}

/*****************************************************************************/

bool RationalNumber::operator < (const RationalNumber & _rhs)
{
	double lhs = (double) *this;
	double rhs = (double)_rhs;

	return lhs < rhs;
}

/*****************************************************************************/

void RationalNumber::operator *= (const RationalNumber & _rhs)
{
	m_numerator *= _rhs.m_numerator;
	m_denominator *= _rhs.m_denominator;

	simplifing();
}

/*****************************************************************************/

RationalNumber RationalNumber::operator * (const RationalNumber & _rhs)
{
	int numerator = m_numerator * _rhs.m_numerator;
	int denominator = m_denominator * _rhs.m_denominator;

	return RationalNumber(numerator, denominator);
}

/*****************************************************************************/

RationalNumber RationalNumber::operator + (const RationalNumber & _rhs)
{
	int most = greatest(this->m_denominator, _rhs.m_denominator);
	int lhs_n = m_numerator * (most / this->m_denominator);
	int rhs_n = _rhs.m_numerator * (most / _rhs.m_denominator);

	return RationalNumber(lhs_n + rhs_n, most);
}

/*****************************************************************************/

void RationalNumber::operator += (const RationalNumber & _rhs)
{
	int most = greatest(this->m_denominator, _rhs.m_denominator);
	int rhs_n = _rhs.m_numerator * (most / _rhs.m_denominator);

	m_numerator *= (most / this->m_denominator);
	m_numerator += rhs_n;
	m_denominator = most;

	simplifing();
}

/*****************************************************************************/

void RationalNumber::operator -= (const RationalNumber & _rhs)
{
	int most = greatest(this->m_denominator, _rhs.m_denominator);
	int rhs_n = _rhs.m_numerator * (most / _rhs.m_denominator);

	m_numerator *= (most / this->m_denominator);
	if (m_numerator - rhs_n == 0)
	{
		m_denominator = 1;
		m_numerator = 0;
	}
	m_numerator -= rhs_n;
	m_denominator = most;

	simplifing();
}

/*****************************************************************************/

RationalNumber RationalNumber::operator - (const RationalNumber & _rhs)
{
	int most = greatest(this->m_denominator, _rhs.m_denominator);
	int lhs_n = m_numerator * (most / this->m_denominator);
	int rhs_n = _rhs.m_numerator * (most / _rhs.m_denominator);
	
	if (lhs_n - rhs_n == 0) 
		return RationalNumber(0, 1);
	return RationalNumber(lhs_n - rhs_n, most);
}

/*****************************************************************************/

RationalNumber RationalNumber::operator / (const RationalNumber & _rhs)
{

	int numerator = m_numerator * _rhs.m_denominator;
	int denominator = m_denominator *_rhs.m_numerator;

	return RationalNumber(numerator, denominator);
}

/*****************************************************************************/

void RationalNumber::operator /= (const RationalNumber & _rhs)
{
	m_numerator *= _rhs.m_denominator;
	m_denominator *= _rhs.m_numerator;

	simplifing();
}

/*****************************************************************************/

RationalNumber::operator double() const
{
	return (double)m_numerator / (double)m_denominator;
}

/*****************************************************************************/

std::ostream & operator << (std::ostream & _stream, const RationalNumber & _rn)
{
	_stream << _rn.m_numerator << "/" << _rn.m_denominator;
	return _stream;
}

/*****************************************************************************/