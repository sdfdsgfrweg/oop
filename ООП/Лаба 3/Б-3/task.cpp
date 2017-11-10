// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "task.hpp"
#include "messages.hpp"
#include "employee.hpp"
#include <iostream>

/*****************************************************************************/

Task::Task(std::string const & _tastName)
	: m_taskName(_tastName)
{}

/*****************************************************************************/

Task::~Task() = default;

/*****************************************************************************/

void Task::addTaskData(Employee & _e, int _hours)
{
	m_employers.insert(std::make_pair(_e.getName(), std::make_pair(_hours, &_e)));
}

/*****************************************************************************/

void Task::removeEmployer(std::string const & _e)
{
	auto it = m_employers.find(_e);
	m_employers.erase(it);
}

/*****************************************************************************/

void Task::updateEmployerTime(std::string const & _e, int _newTime)
{
	auto it = m_employers.find(_e);
	it->second.first = _newTime;
}

/*****************************************************************************/

void Task::forEachEmployee(std::function<void(Employee const & _e)> _f)
{
	for (auto const & e : m_employers)
		_f(*e.second.second);
}

/*****************************************************************************/