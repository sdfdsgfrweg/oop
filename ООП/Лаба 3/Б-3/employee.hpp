// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _EMPLOYEE_HPP_
#define _EMPLOYEE_HPP_

/*****************************************************************************/

#include <string>
#include <unordered_map>
#include <functional>

/*****************************************************************************/

class Task;

/*****************************************************************************/

class Employee
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Employee(
		std::string const & _fullName,
		int _qualificationLevel
	);

	~Employee();

	std::string const & getName() const;

	int getQualificationLevel() const;

	void updateQualificationLevel(int _newLevel);

	void addTask(Task & _task);

	void removeTask(std::string const & _task);

	void forEachTask(std::function<void(Task const & _t)> _f);

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::string m_fullName;
	int m_qualificationLevel;
	std::unordered_map<std::string,Task *> m_tasks;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
std::string const & Employee::getName() const
{
	return m_fullName;
}

/*****************************************************************************/

inline
int Employee::getQualificationLevel() const
{
	return m_qualificationLevel;
}

/*****************************************************************************/

#endif //  _EMPLOYEE_HPP_