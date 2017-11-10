// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

/*****************************************************************************/

class Task;
class Employee;

class Controller
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Controller();

	~Controller();

	Controller(const Controller &) = delete;

	Controller & operator = (const Controller &) = delete;

	/*-----------------------------------------------------------------*/

	void createEmployee(std::string const & _fullName, int _level);

	void updateEmployeeLevel(std::string const & _fullName, int _newLevel);

	int getEmployeeLevel(std::string const & _fullName) const;

	/*-----------------------------------------------------------------*/

	void createTask(std::string const & _taskTitle);

	void assignEmployeeToTask(std::string const & _taskTitle,
		std::string const & _employeeName,
		int _hours);

	void updateEmployeeTaskLoad(std::string const & _taskTitle,
		std::string const & _employeeName,
		int _hours);

	void unassignEmployeeFromTask(std::string const & _taskTitle,
		std::string const & _employeeName);

	std::vector< std::string > getTaskEmployees(std::string const & _taskTitle) const;

	std::vector< std::string > getEmployeeTasks(std::string const & _employeeName) const;

	int getEmployeeAllocationInTask(std::string const & _taskTitle,
		std::string const & _employeeName) const;

	/*-----------------------------------------------------------------*/

	int getTaskTotalHours(std::string const & _taskTitle) const;

	std::vector< std::string > getEmployeesWithLoadOver(int _hours) const;

	double calculateTaskCost(std::string const & _taskTitle, double _baseHourCost = 5.00) const;

	double predictEmployeePayment(std::string const & _employeeName, double _baseHourCost = 5.00) const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::unordered_map<std::string, std::unique_ptr<Task> > m_tasks;
	std::unordered_map<std::string, std::unique_ptr<Employee> > m_employers;

	/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_