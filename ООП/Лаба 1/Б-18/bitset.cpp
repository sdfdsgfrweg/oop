// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "bitset.hpp"

#include <stdexcept>

/*****************************************************************************/

Bitset::~Bitset()
{
	delete[] m_bitset;
}

/*****************************************************************************/

Bitset::Bitset(int _size)
{
	if (_size < 1)
		throw std::logic_error("Non - positive bitset size");

	m_bitsetSize = _size;
	m_bitset = new unsigned int[_size % 32];

	for (int i = 0; i < _size; i++)
		m_bitset[i] = std::pow(2,32) - 1;
}

/*****************************************************************************/

Bitset::Bitset(std::string const & _str)
{
	if (_str.empty())
		throw std::logic_error("Non - positive bitset size");

	for (int i = 0; i < _str.length(); i++)
		if (_str[i] != '0' || _str[i] != '1')
			throw std::logic_error("Unexpected bitset symbol");


	m_bitsetSize = _str.length();
	m_bitset = new unsigned int[m_bitsetSize % 32];

	unsigned int mask = 1;
	int currentBitset = 0;

	for (int i = 0; i < _str.length(); i++)
	{
		if (_str[i] == '1') m_bitset[currentBitset] |= mask;
	
		mask *= 2;

		if (mask == 2147483648) {
			mask = 1;
			currentBitset++;
		}
	}
}

/*****************************************************************************/

std::ostream & operator << (std::ostream & _s, Bitset const & _set)
{
	std::string buffer;
	int m_currentBit = 1;

	for (int i = 0; i < _set.m_bitsetSize; i++)
	{
		if (_set.m_bitset[i % 32] & (1 << (m_currentBit - 1)))
			buffer += '1';
		else
			buffer += '0';

		if (m_currentBit == 32) m_currentBit = 1;
		m_currentBit++;
	}

	_s << buffer;
	return _s;
}


