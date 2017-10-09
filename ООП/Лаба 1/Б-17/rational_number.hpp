// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _RATIONAL_NUMBER_HPP_
#define _RATIONAL_NUMBER_HPP_

/*****************************************************************************/

#include <iostream>

/*****************************************************************************/


class RationalNumber
{

/*-----------------------------------------------------------------*/

public:

/*------------------------------------------------------------------*/
	RationalNumber(
		int _numerator,
		int _denumerator
	);

	~RationalNumber() = default;

	int getNumerator() const;

	int getDenominator() const;

	bool operator == (const RationalNumber & _rhs);

	bool operator != (const RationalNumber & _rhs);

	bool operator >= (const RationalNumber & _rhs);

	bool operator <= (const RationalNumber & _rhs);

	bool operator > (const RationalNumber & _rhs);

	bool operator < (const RationalNumber & _rhs);

	void operator *= (const RationalNumber & _rhs);

	RationalNumber operator * (const RationalNumber & _rhs);

	RationalNumber operator + (const RationalNumber & _rhs);

	void operator += (const RationalNumber & _rhs);

	void operator -= (const RationalNumber & _rhs);

	RationalNumber operator - (const RationalNumber & _rhs);

	RationalNumber operator / (const RationalNumber & _rhs);

	void operator /= (const RationalNumber & _rhs);

/*------------------------------------------------------------------*/
private:

	void simplifing();

private:
	
	int m_numerator;
	int m_denominator;

};


/*****************************************************************************/

inline int RationalNumber::getNumerator() const
{
	return m_numerator;
}

/*****************************************************************************/

inline int RationalNumber::getDenominator() const
{
	return m_denominator;
}


/*****************************************************************************/

#endif //  _RATIONAL_NUMBER_HPP_
