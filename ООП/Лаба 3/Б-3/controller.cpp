// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "employee.hpp"
#include "task.hpp"
#include <algorithm>

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::createEmployee(
	std::string const & _fullName,
	int _level
)
{
	if (_fullName.empty())
		throw std::logic_error(Messages::EmptyEmployeeName);

	auto it = m_employers.find(_fullName);
	if (it != m_employers.end())
		throw std::logic_error(Messages::EmployeeAlreadyExists);

	if (_level < 1 || _level > 5)
		throw std::logic_error(Messages::LevelOutOfRange);

	m_employers.insert(std::make_pair(_fullName, std::make_unique<Employee>(_fullName, _level)));
}

/*****************************************************************************/

void Controller::updateEmployeeLevel(
	std::string const & _fullName,
	int _newLevel
)
{
	auto it = m_employers.find(_fullName);
	if (it == m_employers.end())
		throw std::logic_error(Messages::EmployeeNotFound);

	if (_newLevel < 1 || _newLevel > 5)
		throw std::logic_error(Messages::LevelOutOfRange);
	
	it->second->updateQualificationLevel(_newLevel);
}

/*****************************************************************************/

int Controller::getEmployeeLevel(std::string const & _fullName) const
{
	auto it = m_employers.find(_fullName);
	if (it == m_employers.end())
		throw std::logic_error(Messages::EmployeeNotFound);

	return it->second->getQualificationLevel();
}

/*****************************************************************************/

void Controller::createTask(std::string const & _taskTitle)
{
	if (_taskTitle.empty())
		throw std::logic_error(Messages::EmptyTaskTitle);

	auto it = m_tasks.find(_taskTitle);
	if (it != m_tasks.end())
		throw std::logic_error(Messages::TaskAlreadyExists);

	m_tasks.insert(std::make_pair(_taskTitle, std::make_unique<Task>(_taskTitle)));
}

/*****************************************************************************/

void Controller::assignEmployeeToTask(
	std::string const & _taskTitle,
	std::string const & _employeeName,
	int _hours
)
{
	auto it1 = m_tasks.find(_taskTitle);
	if (it1 == m_tasks.end())
		throw std::logic_error(Messages::TaskNotFound);

	auto it2 = m_employers.find(_employeeName);	
	if (it2 == m_employers.end())
		throw std::logic_error(Messages::EmployeeNotFound);

	if (_hours < 1)
		throw std::logic_error(Messages::NonPositiveHours);

	if (it1->second->hasEmployee(_employeeName))
		throw std::logic_error(Messages::EmployeeAlreadyAllocated);

	it2->second->addTask(*it1->second);
	it1->second->addTaskData(*it2->second, _hours);
}

/*****************************************************************************/

void Controller::updateEmployeeTaskLoad(
	std::string const & _taskTitle,
	std::string const & _employeeName,
	int _hours
)
{
	auto it1 = m_tasks.find(_taskTitle);
	if (it1 == m_tasks.end())
		throw std::logic_error(Messages::TaskNotFound);

	auto it2 = m_employers.find(_employeeName);
	if (it2 == m_employers.end())
		throw std::logic_error(Messages::EmployeeNotFound);

	if (_hours < 1)
		throw std::logic_error(Messages::NonPositiveHours);

	if (!it1->second->hasEmployee(_employeeName))
		throw std::logic_error(Messages::EmployeeNotAllocated);
	
	it1->second->updateEmployerTime(_employeeName, _hours);
}

/*****************************************************************************/

void Controller::unassignEmployeeFromTask(
	std::string const & _taskTitle,
	std::string const & _employeeName
)
{
	auto it1 = m_tasks.find(_taskTitle);
	if (it1 == m_tasks.end())
		throw std::logic_error(Messages::TaskNotFound);

	auto it2 = m_employers.find(_employeeName);
	if (it2 == m_employers.end())
		throw std::logic_error(Messages::EmployeeNotFound);

	if (!it1->second->hasEmployee(_employeeName))
		throw std::logic_error(Messages::EmployeeNotAllocated);

	it1->second->removeEmployer(_employeeName);
	it2->second->removeTask(_taskTitle);
}

/*****************************************************************************/

std::vector<std::string> 
Controller::getTaskEmployees(std::string const & _taskTitle) const
{
	std::vector<std::string> result;

	auto it = m_tasks.find(_taskTitle);
	if (it == m_tasks.end())
		throw std::logic_error(Messages::TaskNotFound);

	it->second->forEachEmployee(
		[&](Employee const & _e)
	{
		result.push_back(_e.getName());
	}
	);

	std::sort(
		result.begin(),
		result.end()
	);

	return result;
}

/*****************************************************************************/

std::vector<std::string> 
Controller::getEmployeeTasks(std::string const & _employeeName) const
{
	std::vector<std::string> result;

	auto it = m_employers.find(_employeeName);
	if (it == m_employers.end())
		throw std::logic_error(Messages::EmployeeNotFound);

	it->second->forEachTask(
		[&](Task const & _task)
	{
		result.push_back(_task.getTaskName());
	}
	);

	std::sort(
		result.begin(),
		result.end()
	);

	return result;
}

/*****************************************************************************/

int Controller::getEmployeeAllocationInTask(
	std::string const & _taskTitle,
	std::string const & _employeeName
) const
{
	auto it1 = m_employers.find(_employeeName);
	if (it1 == m_employers.end())
		throw std::logic_error(Messages::EmployeeNotFound);

	auto it2 = m_tasks.find(_taskTitle);
	if (it2 == m_tasks.end())
		throw std::logic_error(Messages::TaskNotFound);

	return it2->second->getEmployeeHours(_employeeName);
}

/*****************************************************************************/

int Controller::getTaskTotalHours(std::string const & _taskTitle) const
{
	auto it = m_tasks.find(_taskTitle);
	if (it == m_tasks.end())
		throw std::logic_error(Messages::TaskNotFound);

	int total = 0;
	it->second->forEachEmployee(
		[&](Employee const & _e)
	{
		total += it->second->getEmployeeHours(_e.getName());
	}
	);

	return total;
}

/*****************************************************************************/

std::vector<std::string> 
Controller::getEmployeesWithLoadOver(int _hours) const
{
	std::vector<std::string> result;
	
	int totalEmployeeHours;
	for (auto const & pEmployee : m_employers)
	{
		totalEmployeeHours = 0;
		pEmployee.second->forEachTask(
			[&](Task const & _task)
		{
			totalEmployeeHours += _task.getEmployeeHours(pEmployee.first);
		}
		);

		if (totalEmployeeHours > _hours)
			result.push_back(pEmployee.first);
	}
	std::sort(result.begin(), result.end());

	return result;
}

/*****************************************************************************/

double Controller::calculateTaskCost(
	std::string const & _taskTitle,
	double _baseHourCost
) const
{

	auto it = m_tasks.find(_taskTitle);
	if (it == m_tasks.end())
		throw std::logic_error(Messages::TaskNotFound);

	if (_baseHourCost < 0)
		throw std::logic_error(Messages::NegativeHourCost);

	double totalCost = 0.0;

	it->second->forEachEmployee(
		[&](Employee const & _e)
	{
		totalCost += _e.getQualificationLevel() * it->second->getEmployeeHours(_e.getName()) * _baseHourCost;
	}
	);

	return totalCost;
}

/*****************************************************************************/

double Controller::predictEmployeePayment(
	std::string const & _employeeName,
	double _baseHourCost
) const
{
	auto it = m_employers.find(_employeeName);
	if (it == m_employers.end())
		throw std::logic_error(Messages::EmployeeNotFound);

	if (_baseHourCost < 0)
		throw std::logic_error(Messages::NegativeHourCost);

	double totalPayment = 0.0;

	it->second->forEachTask(
		[&](Task const & _task)
	{
		totalPayment += _task.getEmployeeHours(_employeeName) * it->second->getQualificationLevel() * _baseHourCost;
	}
	);

	return totalPayment;
}

/*****************************************************************************/