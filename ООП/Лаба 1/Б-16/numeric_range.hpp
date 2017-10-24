// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _NUMERIC_RANGE_HPP_
#define _NUMERIC_RANGE_HPP_

/*****************************************************************************/

#include <iostream>

/*****************************************************************************/


class NumericRange
{
public:

	class Iterator
	{

		/*-------------------------------------------------------------*/

	public:

		/*-------------------------------------------------------------*/

		// явный конструктор
		explicit Iterator(int _currentPosition);

		// ќператоры разыменовывани€ с целью чтени€ и записи
		int operator * () const;

		// ќператоры сравнени€ на равенство и неравенство
		bool operator == (Iterator i) const;
		bool operator != (Iterator i) const;

		// ќператоры префиксного и постфиксного инкремента
		Iterator & operator ++ ();
		Iterator operator ++ (int);

		/*-------------------------------------------------------------*/

	private:

		/*-------------------------------------------------------------*/

		friend class NumericRange;
		/*-------------------------------------------------------------*/

		int m_currentPosition;

		/*-------------------------------------------------------------*/

	};


/*-----------------------------------------------------------------*/

public:

	NumericRange();

	NumericRange(int _low, int _high);

	NumericRange(std::string const & _str);

	int getLowBound() const;

	int getHighBound() const;

	int getWidth() const;

	bool contains(int _number) const;

	bool intersectsWith(NumericRange const & _nr) const;

	bool includes(NumericRange const & _nr) const;

	bool belongsTo(NumericRange const & _nr) const;

	bool adjacentTo(NumericRange const & _nr) const;

	bool operator ==(NumericRange const & _nr) const;

	bool operator !=(NumericRange const & _nr) const;

	bool operator >=(NumericRange const & _nr) const;

	bool operator <=(NumericRange const & _nr) const;

	bool operator <(NumericRange const & _nr) const;

	bool operator >(NumericRange const & _nr) const;

	Iterator begin() const;

	Iterator end() const;

	friend std::ostream & operator << (std::ostream & _s, NumericRange const & _nr);


/*------------------------------------------------------------------*/

private:

	int m_lowBound, m_highBound;
	

/*------------------------------------------------------------------*/

};

/*****************************************************************************/

inline
int NumericRange::getLowBound() const
{
	return m_lowBound;
}

/*****************************************************************************/

inline
int NumericRange::getHighBound() const
{
	return m_highBound;
}

/*****************************************************************************/

inline
int NumericRange::getWidth() const
{
	return m_highBound - m_lowBound + 1;
}

/*****************************************************************************/

inline
bool NumericRange::contains(int _number) const
{
	for (int i = m_lowBound; i < m_highBound + 1; i++)
		if (i == _number) return true;
	return false;
}

/*****************************************************************************/

inline
bool NumericRange::intersectsWith(NumericRange const & _nr) const
{
	if (m_lowBound <= _nr.m_lowBound && m_highBound >= _nr.m_lowBound) return true;
	
	if (m_lowBound <= _nr.m_highBound && m_highBound >= _nr.m_highBound) return true;

	if (m_lowBound >= _nr.m_lowBound && m_lowBound <= _nr.m_highBound) return true;

	if (m_highBound >= _nr.m_lowBound && m_highBound <= _nr.m_highBound) return true;
	
	return false;
}

/*****************************************************************************/

inline
bool NumericRange::includes(NumericRange const & _nr) const
{
	return _nr.m_lowBound >= m_lowBound && _nr.m_highBound <= m_highBound;
}

/*****************************************************************************/

inline
bool NumericRange::belongsTo(NumericRange const & _nr) const
{
	return _nr.m_lowBound <= m_lowBound && _nr.m_highBound >= m_highBound;
}

/*****************************************************************************/

inline
bool NumericRange::adjacentTo(NumericRange const & _nr) const
{
	return _nr.m_highBound < m_lowBound || _nr.m_lowBound > m_highBound;
}

/*****************************************************************************/

inline
bool NumericRange::operator ==(NumericRange const & _nr) const
{
	return _nr.m_lowBound == m_lowBound && _nr.m_highBound == m_highBound;
}

/*****************************************************************************/

inline
bool NumericRange::operator !=(NumericRange const & _nr) const
{
	return !(*this == _nr);
}

/*****************************************************************************/

inline
bool NumericRange::operator >=(NumericRange const & _nr) const
{
	return m_lowBound > _nr.m_lowBound || (m_lowBound == _nr.m_lowBound && m_highBound >= _nr.m_highBound);
}

/*****************************************************************************/

inline
bool NumericRange::operator <=(NumericRange const & _nr) const
{
	return m_lowBound < _nr.m_lowBound || (m_lowBound == _nr.m_lowBound && m_highBound <= _nr.m_highBound);
}

/*****************************************************************************/

inline
bool NumericRange::operator <(NumericRange const & _nr) const
{
	return m_lowBound < _nr.m_lowBound || (m_lowBound == _nr.m_lowBound && m_highBound < _nr.m_highBound);
}

/*****************************************************************************/

inline
bool NumericRange::operator >(NumericRange const & _nr) const
{
	return m_lowBound > _nr.m_lowBound || (m_lowBound == _nr.m_lowBound && m_highBound > _nr.m_highBound);
}

/*****************************************************************************/

inline
NumericRange::Iterator NumericRange::begin() const
{
	return Iterator(m_lowBound);
}

/*****************************************************************************/

inline
NumericRange::Iterator NumericRange::end() const
{
	return Iterator(m_highBound + 1);
}

/*****************************************************************************/


#endif //  _NUMERIC_RANGE_HPP_
