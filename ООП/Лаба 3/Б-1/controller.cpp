// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "academicgroup.hpp"
#include "student.hpp"
#include "messages.hpp"

#include <algorithm>

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::createStudent(int _studentId, const std::string & _fullName, Date _birthday, StudyForm _studyForm)
{
	if (m_students.find(_studentId) != m_students.end())
		throw std::logic_error(Messages::StudentIdNotUnique);

	if (_fullName.empty())
		throw std::logic_error(Messages::InvalidStudentName);

	if (_birthday >= Date())
		throw std::logic_error(Messages::StudentBirthdayTooLate);

	m_students.insert(std::make_pair(_studentId, std::make_unique<Student>(_studentId, _fullName, _birthday, _studyForm)));
}

/*****************************************************************************/

const std::string & Controller::getStudentName(int _studentId) const
{
	if (m_students.find(_studentId) == m_students.end())
		throw std::logic_error(Messages::StudentNotFound);

	return m_students.find(_studentId)->second->getName();
}

/*****************************************************************************/

Date Controller::getStudentBirthday(int _studentId) const
{
	if (m_students.find(_studentId) == m_students.end())
		throw std::logic_error(Messages::StudentNotFound);

	return m_students.find(_studentId)->second->getBirthDay();
}

/*****************************************************************************/

StudyForm Controller::getStudentStudyForm(int _studentId) const
{
	if (m_students.find(_studentId) == m_students.end())
		throw std::logic_error(Messages::StudentNotFound);

	return m_students.find(_studentId)->second->getStudyForm();
}

/*****************************************************************************/

void Controller::createGroup(const std::string & _groupName)
{
	if (m_groups.find(_groupName) != m_groups.end())
		throw std::logic_error(Messages::GroupNameNotUnique);

	if (_groupName.empty())
		throw std::logic_error(Messages::InvalidGroupName);

	m_groups.insert(std::make_pair(_groupName, std::make_unique<AcademicGroup>(_groupName)));
}

/*****************************************************************************/

void Controller::addStudentToGroup(int _studentId, const std::string & _groupName)
{
	if (m_students.find(_studentId) == m_students.end())
		throw std::logic_error(Messages::StudentNotFound);

	if (m_groups.find(_groupName) == m_groups.end())
		throw std::logic_error(Messages::GroupNotFound);

	for (auto const & g : m_groups)
		if (g.second->hasStudent(_studentId) && g.first != _groupName)
			throw std::logic_error(Messages::StudentCannotStudyInTwoGroups);

	m_groups.find(_groupName)->second->addStudent(*m_students.find(_studentId)->second.get());
}

/*****************************************************************************/

void Controller::removeStudentFromGroup(int _studentId, const std::string & _groupName)
{
	if (m_students.find(_studentId) == m_students.end())
		throw std::logic_error(Messages::StudentNotFound);

	if (m_groups.find(_groupName) == m_groups.end())
		throw std::logic_error(Messages::GroupNotFound);

	for (auto const & g : m_groups)
		if (!g.second->hasStudent(_studentId))
			throw std::logic_error(Messages::RemovingStudentNotInGroup);

	m_groups.find(_groupName)->second->removeStudent(_studentId);
}

/*****************************************************************************/

std::vector<int> Controller::getStudentIdsOfGroup(const std::string & _groupName) const
{
	if (m_groups.find(_groupName) == m_groups.end())
		throw std::logic_error(Messages::GroupNotFound);

	std::vector<int> result;
	
	m_groups.find(_groupName)->second->forEachStudent(
		[&](Student const & _s)
	{
		result.push_back(_s.getID());
	}
	);

	std::sort(result.begin(), result.end());
	
	return result;
}

/*****************************************************************************/

void Controller::assignGroupCaptain(int _studentId, const std::string & _groupName)
{
	if (m_students.find(_studentId) == m_students.end())
		throw std::logic_error(Messages::StudentNotFound);

	if (m_groups.find(_groupName) == m_groups.end())
		throw std::logic_error(Messages::GroupNotFound);

	if (!m_groups.find(_groupName)->second->hasStudent(_studentId))
		throw std::logic_error(Messages::CaptainMustStudyInGroup);

	m_groups.find(_groupName)->second->addMajorStudent(*m_students.find(_studentId)->second.get());
}

/*****************************************************************************/

int Controller::getGroupCaptainId(const std::string & _groupName) const
{
	if (m_groups.find(_groupName) == m_groups.end())
		throw std::logic_error(Messages::GroupNotFound);

	return m_groups.find(_groupName)->second->hasMajorStudent() ? m_groups.find(_groupName)->second->getMajorStudent().getID() : -1;
}

/*****************************************************************************/

int Controller::getStudentsCountPerStudyForm(StudyForm _studyForm) const
{
	int total = 0;

	for (auto const & g : m_groups)
		g.second->forEachStudent(
			[&](Student const & _s)
	{
		if (_s.getStudyForm() == _studyForm)
			total++;
	}
	);

	return total;
}

/*****************************************************************************/

double Controller::getBudgetStudentsPercentageInGroup(std::string const & _groupName) const
{
	if (m_groups.find(_groupName) == m_groups.end())
		throw std::logic_error(Messages::GroupNotFound);

	double percents = 0.0;
	int total = 0, onBudget = 0;
	m_groups.find(_groupName)->second->forEachStudent(
		[&](Student const & _s)
	{
		if (_s.getStudyForm() == StudyForm::Budget)
			onBudget++;
		total++;
	}
	);

	percents = (onBudget * 100) / total;

	return percents;
}

/*****************************************************************************/

std::vector<int> Controller::getStudentsBornFirstDayOfMonth() const
{
	std::vector<int> students;

	for (auto const & s : m_students)
		if (s.second->getBirthDay().getDay() == 1)
			students.push_back(s.first);

	return students;
}

/*****************************************************************************/

std::string Controller::getEldestCaptainName() const
{
	std::string captain;
	Date d;

	for (auto const & g : m_groups)
		if (g.second->hasMajorStudent())
			if (g.second->getMajorStudent().getBirthDay() < d)
			{
				d = g.second->getMajorStudent().getBirthDay();
				captain = g.second->getMajorStudent().getName();
			}

	return captain;
}

/*****************************************************************************/