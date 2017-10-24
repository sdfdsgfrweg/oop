// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "rational_number.hpp"

#include <stdexcept>

//нахождение найменьшего общего делимого
int RationalNumber::getTheMost(int _left, int _rn)
{
	if (_left == _rn) return _left;

	int getTheMost = _left * _rn;
	int minimum = 0;
	for (int i = getTheMost; i >= 1; i--)
		if (i % _left == 0 && i % _rn == 0) minimum = i;
	return minimum;
}

//конструктор
RationalNumber::RationalNumber(
	int _num,
	int _denom
)
{
	if (_denom == 0)
		throw std::logic_error("Zero denominator");

	bool minus = false;
	
	if (_denom < 0 || _num < 0)  
		minus = true;
	
	if (_denom < 0 && _num < 0) 
		minus = false;

	m_num = std::abs(_num);
	m_denom = std::abs(_denom);
	
	int minimum = 1;
	for (int i = 1; i < m_num + 1; i++)
		if (m_num % i == 0 && m_denom % i == 0 && i != 1)
		{
			minimum = i;
		}

	while (m_num % minimum == 0 && m_denom % minimum == 0)
	{
		if (minimum == 1)
			break;
		m_num /= minimum;
		m_denom /= minimum;
	}

	if (minus) m_num = -m_num;
}

bool RationalNumber::operator == (const RationalNumber & _rn)
{
	return m_num == _rn.m_num && m_denom == _rn.m_denom;
}

bool RationalNumber::operator != (const RationalNumber & _rn)
{
	return !(*this == _rn);
}

bool RationalNumber::operator >= (const RationalNumber & _rn)
{
	double left = (double) *this;
	double right = (double)_rn;

	return left >= right;
}

bool RationalNumber::operator <= (const RationalNumber & _rn) 
{
	double left = (double) *this;
	double right = (double)_rn;

	return left <= right;
}

bool RationalNumber::operator > (const RationalNumber & _rn)
{
	double left = (double) *this;
	double right = (double)_rn;

	return left > right;
}

bool RationalNumber::operator < (const RationalNumber & _rn)
{
	double left = (double) *this;
	double right = (double)_rn;

	return left < right;
}

void RationalNumber::operator *= (const RationalNumber & _rn)
{
	m_num *= _rn.m_num;
	m_denom *= _rn.m_denom;
	
	int minimum = 1;
	for (int i = 1; i < m_num + 1; i++)
		if (m_num % i == 0 && m_denom % i == 0 && i != 1)
		{
			minimum = i;
		}

	while (m_num % minimum == 0 && m_denom % minimum == 0)
	{
		if (minimum == 1) 
			break;
		m_num /= minimum;
		m_denom /= minimum;
	}
}

RationalNumber RationalNumber::operator * (const RationalNumber & _rn)
{
	int numerator = m_num * _rn.m_num;
	int denominator = m_denom * _rn.m_denom;

	return RationalNumber(numerator, denominator);
}

RationalNumber RationalNumber::operator + (const RationalNumber & _rn)
{
	int most = getTheMost(m_denom, _rn.m_denom);
	int left_n = m_num * (most / m_denom);
	int right_n = _rn.m_num * (most / _rn.m_denom);

	return RationalNumber(left_n + right_n, most);
}

void RationalNumber::operator += (const RationalNumber & _rn)
{
	int most = getTheMost(m_denom, _rn.m_denom);
	int right_n = _rn.m_num * (most / _rn.m_denom);

	m_num *= (most / m_denom);
	m_num += right_n;
	m_denom = most;
	int minimum = 1;
	for (int i = 1; i < m_num + 1; i++)
		if (m_num % i == 0 && m_denom % i == 0 && i != 1)
		{
			minimum = i;
		}

	while (m_num % minimum == 0 && m_denom % minimum == 0)
	{
		if (minimum == 1)
			break;
		m_num /= minimum;
		m_denom /= minimum;
	}
}

void RationalNumber::operator -= (const RationalNumber & _rn)
{
	int most = getTheMost(m_denom, _rn.m_denom);
	int right_n = _rn.m_num * (most / _rn.m_denom);

	m_num *= (most / m_denom);
	if (m_num - right_n == 0)
	{
		m_denom = 1;
		m_num = 0;
	}
	m_num -= right_n;
	m_denom = most;
	int minimum = 1;
	for (int i = 1; i < m_num + 1; i++)
		if (m_num % i == 0 && m_denom % i == 0 && i != 1)
		{
			minimum = i;
		}

	while (m_num % minimum == 0 && m_denom % minimum == 0)
	{
		if (minimum == 1)
			break;
		m_num /= minimum;
		m_denom /= minimum;
	}
}

RationalNumber RationalNumber::operator - (const RationalNumber & _rn)
{
	int most = getTheMost(m_denom, _rn.m_denom);
	int left_n = m_num * (most / m_denom);
	int right_n = _rn.m_num * (most / _rn.m_denom);
	
	if (left_n - right_n == 0) 
		return RationalNumber(0, 1);
	return RationalNumber(left_n - right_n, most);
}

RationalNumber RationalNumber::operator / (const RationalNumber & _rn)
{

	int numerator = m_num * _rn.m_denom;
	int denominator = m_denom *_rn.m_num;

	return RationalNumber(numerator, denominator);
}

void RationalNumber::operator /= (const RationalNumber & _rn)
{
	m_num *= _rn.m_denom;
	m_denom *= _rn.m_num;

	int minimum = 1;
	for (int i = 1; i < m_num + 1; i++)
		if (m_num % i == 0 && m_denom % i == 0 && i != 1)
		{
			minimum = i;
		}

	while (m_num % minimum == 0 && m_denom % minimum == 0)
	{
		if (minimum == 1)
			break;
		m_num /= minimum;
		m_denom /= minimum;
	}
}

RationalNumber::operator double() const
{
	return (double)m_num / (double)m_denom;
}

std::ostream & operator << (std::ostream & _stream, const RationalNumber & _rn)
{
	_stream << _rn.m_num << "/" << _rn.m_denom;
	return _stream;
}