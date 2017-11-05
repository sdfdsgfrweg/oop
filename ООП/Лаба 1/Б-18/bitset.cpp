// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "bitset.hpp"

#include <stdexcept>

/*****************************************************************************/

//Bitset::~Bitset()
//{
//	delete[] m_bitset;
//}

bool Bitset::isSet(int _index) const
{
	if (_index < 0 || _index >= m_bitsetSize)
		throw std::logic_error("Index out of range");

	int up = 32, count = 0;
	while (up < _index) {
		up <<= 1;
		count++;
	}
		
	return m_bitset[count] & (1 << ((_index % 32)));
}

void Bitset::set(int _index)
{
	if (_index < 0 || _index >= m_bitsetSize)
		throw std::logic_error("Index out of range");

	int up = 32, count = 0;
	while (up < _index) {
		up <<= 1;
		count++;
	}

	m_bitset[count] |= (1 << (_index % 32));
}

void Bitset::clear(int _index)
{
	if (_index < 0 || _index >= m_bitsetSize)
		throw std::logic_error("Index out of range");

	int up = 32, count = 0;
	while (up < _index) {
		up <<= 1;
		count++;
	}

	m_bitset[count] &= ~(1 << (_index % 32));
}

void Bitset::clearAll()
{
	int currentBitset = 0;
	for (int i = 0; i < m_bitsetSize; i++)
	{
		if (i == 32) currentBitset++;
		m_bitset[currentBitset] &= ~(1 << i);
	}
}

Bitset & Bitset::operator~()
{
	for (int i = 0; i < m_bitsetSize; i++)
	{
		if (m_bitset[i / 32] & (1 << i))
			m_bitset[i / 32] &= ~(1 << i);
		else
			m_bitset[i / 32] |= (1 << i);
	}

	return * this;
}

bool Bitset::operator!() const
{
	for (int i = 0; i < m_bitsetSize; i++)
	{
		if (m_bitset[i / 32] & (1 << i)) return false;
	}

	return true;
}

bool Bitset::operator()()
{

	return !!*this;
}

/*****************************************************************************/

Bitset::Bitset(int _size)
{
	if (_size < 1)
		throw std::logic_error("Non-positive bitset size");

	m_bitsetSize = _size;
	int arraySize = (m_bitsetSize / 32) + 1;
	m_bitset = new unsigned int[arraySize];
	
	for (int i = 0; i < arraySize; i++) m_bitset[i] = 1 << 32;
}

/*****************************************************************************/

Bitset::Bitset(std::string const & _str)
{
	if (_str.empty())
		throw std::logic_error("Non-positive bitset size");

	for (int i = 0; i < _str.length(); i++)
	{
		if (_str[i] == '0' || _str[i] == '1')
			continue;
		else
			throw std::logic_error("Unexpected bitset symbol");
	}
		
	m_bitsetSize = _str.length();
	int arraySize = m_bitsetSize / 32 + 1;

	m_bitset = new unsigned int[arraySize];

	for (int i = 0; i < arraySize; i++) m_bitset[i] = 1 << 32;
	
	unsigned int mask = 1;
	int currentBitset = 0;

	for (int i = 0; i < _str.length(); i++)
	{
		if (i == 32) currentBitset++;
		if (_str[i] == '1')
			m_bitset[currentBitset] |= (1 << i);
	}
}

Bitset & Bitset::operator=(Bitset const & _b)
{
	if (&_b == this) return * this;

	int copyingSize = _b.m_bitsetSize / 32 + 1;
	m_bitsetSize = _b.m_bitsetSize;
	m_bitset = new unsigned int[copyingSize];
	for (int i = 0; i < copyingSize; i++)
		m_bitset[i] = _b.m_bitset[i];

	return * this;
}

Bitset Bitset::operator & (Bitset & _b) const
{

	Bitset _new(*this);

	int size = (m_bitsetSize / 32) + 1;
	for (int i = 0; i < size; i++)
		_new.m_bitset[i] = m_bitset[i] & _b.m_bitset[i];

	return _new;
}

Bitset Bitset::operator | (Bitset & _b) const
{
	Bitset _new(*this);

	int size = (m_bitsetSize / 32) + 1;
	for (int i = 0; i < size; i++)
		_new.m_bitset[i] = m_bitset[i] | _b.m_bitset[i];

	return _new;
}

Bitset & Bitset::operator &= ( Bitset & _b)
{
	int size = (m_bitsetSize / 32) + 1;
	for (int i = 0; i < size; i++)
		m_bitset[i] &= _b.m_bitset[i];

	return *this;
}

Bitset & Bitset::operator |= (Bitset & _b)
{
	int size = (m_bitsetSize / 32) + 1;
	for (int i = 0; i < size; i++)
		m_bitset[i] |= _b.m_bitset[i];

	return *this;
}

Bitset::Bitset(Bitset const & _b)
{
	int copyingSize = _b.m_bitsetSize / 32 + 1;
	m_bitsetSize = _b.m_bitsetSize;

	m_bitset = new unsigned int[copyingSize];
	for (int i = 0; i < copyingSize; i++)
		m_bitset[i] = _b.m_bitset[i];
}

Bitset & Bitset::operator=(Bitset && _b)
{
	if (&_b == this) return * this;

	m_bitsetSize = _b.m_bitsetSize;
	std::swap(m_bitset, _b.m_bitset);

	return *this;
}

Bitset::Bitset(Bitset && _b)
{
	m_bitsetSize = _b.m_bitsetSize;
	std::swap(m_bitset, _b.m_bitset);
}

/*****************************************************************************/

std::ostream & operator << (std::ostream & _s, Bitset const & _set)
{
	std::string buffer;
	
	for (int i = 0; i < _set.m_bitsetSize; i++)
	{
		if (_set.m_bitset[i / 32] & (1 << i))
			buffer += '1';
		else
			buffer += '0';
	}
	
	_s << buffer;
	return _s;
}