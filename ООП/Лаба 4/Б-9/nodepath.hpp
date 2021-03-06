// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _NOTEPATH_HPP_
#define _NOTEPATH_HPP_

/*****************************************************************************/

#include <vector>

/*****************************************************************************/

class NodePath
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	NodePath(int _firstIndex);

	~NodePath();

	/*-----------------------------------------------------------------*/

	NodePath & pushIndex(int _nextIndex);

	int getLevelsCount() const;

	int getIndexAtLevel(int _level) const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::vector< int > m_indexes;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _NOTEPATH_HPP_