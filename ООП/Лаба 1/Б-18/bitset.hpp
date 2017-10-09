// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _BITSET_HPP_
#define _BITSET_HPP_

/*****************************************************************************/

#include <iostream>
#include <string>

/*****************************************************************************/


class Bitset
{

/*-----------------------------------------------------------------*/

public:

/*------------------------------------------------------------------*/

	Bitset(int _size = 32);

	Bitset(std::string const & _str);

	~Bitset();

	friend std::ostream & operator << (std::ostream & _s, Bitset const & _set);

	int getSize() const;

/*------------------------------------------------------------------*/

private:
	
	unsigned int * m_bitset;
	int m_bitsetSize;

};

inline int Bitset::getSize() const
{
	return m_bitsetSize;
}



/*****************************************************************************/

#endif //  _BITSET_HPP_
