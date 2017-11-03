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

	Bitset & operator =(Bitset const & _b);

	Bitset(Bitset const & _b);

	Bitset & operator =(Bitset && _b);

	Bitset(Bitset && _b);

	~Bitset();

	friend std::ostream & operator << (std::ostream & _s, Bitset const & _set);

	bool isSet(int _index) const;

	void set(int _index);

	void clear(int _index);

	void clearAll();

	Bitset & operator ~ ();

	bool operator !() const;

	bool operator ()();

	int getSize() const;

	Bitset & operator & (const Bitset & _b) const;

	Bitset & operator | (const Bitset & _b) const;

	void operator &= (const Bitset & _b);
	
	void operator |= (const Bitset & _b);

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
