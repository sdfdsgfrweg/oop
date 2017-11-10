// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _TASK_HPP_
#define _TASK_HPP_

/*****************************************************************************/

#include <string>
#include <unordered_map>
#include <functional>

/*****************************************************************************/

class Employee;

/*****************************************************************************/


class Task
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Task(std::string const & _tastName);

	~Task();

	std::string const & getTaskName() const;

	void addTaskData(Employee & , int _hours);

	bool hasEmployee(std::string const & _eName) const;

	typedef std::unordered_map<std::string, std::pair<int, Employee *> >::iterator Iter;

	void removeEmployer(std::string const & _e);

	void updateEmployerTime(std::string const & _e, int _newTime);
	
	void forEachEmployee(std::function<void(Employee const & _e)> _f);

	int getEmployeeHours(std::string const & _e) const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::string m_taskName;
	std::unordered_map<std::string, std::pair<int, Employee *>> m_employers;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
std::string const & Task::getTaskName() const
{
	return m_taskName;
}

/*****************************************************************************/

inline
bool Task::hasEmployee(std::string const & _eName) const
{
	return m_employers.find(_eName) != m_employers.end();
}

/*****************************************************************************/

inline
int Task::getEmployeeHours(std::string const & _e) const
{
	return hasEmployee(_e) ? m_employers.find(_e)->second.first : 0;
}

/*****************************************************************************/

#endif //  _TASK_HPP_