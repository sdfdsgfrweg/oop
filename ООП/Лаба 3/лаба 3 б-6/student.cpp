// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "student.hpp"
#include "messages.hpp"
#include "checkpoint.hpp"

/*****************************************************************************/

Student::Student(std::string const & _fullName)
	: m_fullName(_fullName)
{}

/*****************************************************************************/

Student::~Student() = default;

/*****************************************************************************/

void Student::addControlCheckpoint(Checkpoint & _c, int _mark)
{
	auto it = m_controlCheckpoints.find(_c.getName());
	if (it != m_controlCheckpoints.end())
		it->second.second = _mark;
	else
		m_controlCheckpoints.insert(std::make_pair(_c.getName(),std::make_pair(&_c, _mark)));
}

/*****************************************************************************/

int Student::getCheckpointMark(std::string const & _c)
{
	return m_controlCheckpoints.find(_c)->second.second;
}

/*****************************************************************************/

void Student::forEachCheckpoint(std::function<void(Checkpoint const & _e)> _f) const
{
	for (auto const & checkpoint : m_controlCheckpoints)
		_f(*checkpoint.second.first);
}

/*****************************************************************************/