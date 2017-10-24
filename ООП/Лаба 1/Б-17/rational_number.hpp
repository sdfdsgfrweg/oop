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
	RationalNumber(int _num, int _denum);
	~RationalNumber() = default;
	int getNumerator() const;
	int getDenominator() const;
	bool operator == (const RationalNumber & _rn);
	bool operator != (const RationalNumber & _rn);
	bool operator >= (const RationalNumber & _rn);
	bool operator <= (const RationalNumber & _rn);
	bool operator > (const RationalNumber & _rn);
	bool operator < (const RationalNumber & _rn);
	void operator *= (const RationalNumber & _rn);
	RationalNumber operator * (const RationalNumber & _rn);
	RationalNumber operator + (const RationalNumber & _rn);
	void operator += (const RationalNumber & _rn);
	void operator -= (const RationalNumber & _rn);
	RationalNumber operator - (const RationalNumber & _rn);
	RationalNumber operator / (const RationalNumber & _rn);
	void operator /= (const RationalNumber & _rn);
	operator double() const;
	friend std::ostream & operator << (std::ostream & _stream, const RationalNumber & _rn);

/*------------------------------------------------------------------*/


private:

	int getTheMost(int _left, int _rn);

	int m_num;
	int m_denom;
};

inline int RationalNumber::getNumerator() const
{
	return m_num;
}

inline int RationalNumber::getDenominator() const
{
	return m_denom;
}


/*****************************************************************************/

#endif //  _RATIONAL_NUMBER_HPP_
