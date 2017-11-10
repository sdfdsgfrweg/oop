// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "course.hpp"
#include "messages.hpp"
#include "checkpoint.hpp"

/*****************************************************************************/

Course::Course(
	std::string const & _courseName,
	ControlForm _form
)
	: m_courseName(_courseName)
	, m_form(_form)
{}

/*****************************************************************************/

void Course::addCheckpoint(std::unique_ptr<Checkpoint> _c)
{
	m_checkpoints.insert(std::make_pair(_c->getName(),std::move(_c)));
}

/*****************************************************************************/

void Course::forEachCheckpoint(std::function<void(Checkpoint const &)> _f) const
{
	for (auto it = m_checkpoints.begin(); it != m_checkpoints.end(); ++it)
		_f(*it->second.get());
}

/*****************************************************************************/

bool Course::hasCheckpoint(std::string const & _c) const
{
	return m_checkpoints.find(_c) != m_checkpoints.end();
}

/*****************************************************************************/

int Course::getCheckpointSum() const
{
	int total = 0;
	for (auto const & checkpoint : m_checkpoints)
		total += checkpoint.second->getMark();
	return total;
}

/*****************************************************************************/