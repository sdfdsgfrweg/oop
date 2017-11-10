// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "employee.hpp"
#include "messages.hpp"
#include "task.hpp"
#include <iostream>

/*****************************************************************************/

Employee::Employee(
	std::string const & _fullName,
	int _qualificationLevel
)
	: m_fullName(_fullName)
	, m_qualificationLevel(_qualificationLevel)
{}

/*****************************************************************************/

Employee::~Employee() = default;

/*****************************************************************************/

void Employee::updateQualificationLevel(int _newLevel)
{
	m_qualificationLevel = _newLevel;
}

/*****************************************************************************/

void Employee::addTask(Task & _task)
{
	m_tasks.insert(std::make_pair(_task.getTaskName(), &_task));
}

/*****************************************************************************/

void Employee::removeTask(std::string const & _task)
{
	auto it = m_tasks.find(_task);
	m_tasks.erase(it);
}

/*****************************************************************************/

void Employee::forEachTask(std::function<void(Task const & _t)> _f)
{
	for (auto const & t : m_tasks)
		_f(*t.second);
}
/*****************************************************************************/
