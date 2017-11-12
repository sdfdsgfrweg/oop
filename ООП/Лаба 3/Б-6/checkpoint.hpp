// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CHECKPOINT_HPP_
#define _CHECKPOINT_HPP_

/*****************************************************************************/

class Course;

/*****************************************************************************/

#include <string>

class Checkpoint
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Checkpoint(
		std::string const & _name,
		int _mark
	);

	~Checkpoint() = default;

	std::string const & getName() const;

	int getMark() const;

	bool operator < (Checkpoint const & _c) const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::string m_name;
	int m_maxMark;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
std::string const & 
Checkpoint::getName() const
{
	return m_name;
}

/*****************************************************************************/

inline
int Checkpoint::getMark() const
{
	return m_maxMark;
}

/*****************************************************************************/

inline
bool Checkpoint::operator < (Checkpoint const & _c) const
{
	return m_name < _c.m_name;
}

/*****************************************************************************/

#endif // _CHECKPOINT_HPP_