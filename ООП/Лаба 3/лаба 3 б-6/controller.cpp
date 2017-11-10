// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "course.hpp"
#include "student.hpp"
#include "checkpoint.hpp"
#include <algorithm>
#include <iostream>

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::addCourse(const std::string & _courseName, ControlForm _controlForm)
{
	if (_courseName.empty())
		throw std::logic_error(Messages::EmptyCourseName);

	auto it = m_courses.find(_courseName);
	if (it != m_courses.end())
		throw std::logic_error(Messages::DuplicateCourse);

	m_courses.insert(std::make_pair(_courseName, std::make_unique<Course>(_courseName,_controlForm)));
}

/*****************************************************************************/

ControlForm Controller::getCourseControlForm(const std::string & _courseName) const
{
	auto it = m_courses.find(_courseName);
	if (it == m_courses.end())
		throw std::logic_error(Messages::CourseCannotBeFound);

	return it->second->getCourseControlForm();
}

/*****************************************************************************/

void Controller::validateCourseCheckpoints(const std::string & _courseName) const
{
	auto it = m_courses.find(_courseName);
	if (it == m_courses.end())
		throw std::logic_error(Messages::CourseCannotBeFound);

	if (!it->second->hasCheckpoints())
		throw std::logic_error(Messages::NoCheckpointsFound);

	if (it->second->getCheckpointSum() != 100)
		throw std::logic_error(Messages::CheckpointsSumMismatch);
}

/*****************************************************************************/

void Controller::addCheckpoint(
	const std::string & _courseName,
	const std::string & _checkpointName,
	int _maxMark
)
{
	if (_checkpointName.empty())
		throw std::logic_error(Messages::EmptyCheckpointName);

	if (_maxMark < 1 || _maxMark > 100)
		throw std::logic_error(Messages::InvalidMarkValue);

	auto it = m_courses.find(_courseName);
	if (it == m_courses.end())
		throw std::logic_error(Messages::CourseCannotBeFound);

	it->second->addCheckpoint(std::make_unique<Checkpoint>(_checkpointName, _maxMark));
}

/*****************************************************************************/

int Controller::getCheckpointMaxMark(
	const std::string & _courseName,
	const std::string & _checkpointName
) const
{
	auto it = m_courses.find(_courseName);
	if (it == m_courses.end())
		throw std::logic_error(Messages::CourseCannotBeFound);

	if (!it->second->hasCheckpoint(_checkpointName))
		throw std::logic_error(Messages::CheckpointCannotBeFound);

	return it->second->getCheckpoint(_checkpointName).getMark();
}

/*****************************************************************************/

int Controller::getCheckpointMinMark(
	const std::string & _courseName,
	const std::string & _checkpointName
) const
{
	auto it = m_courses.find(_courseName);
	if (it == m_courses.end())
		throw std::logic_error(Messages::CourseCannotBeFound);

	if (!it->second->hasCheckpoint(_checkpointName))
		throw std::logic_error(Messages::CheckpointCannotBeFound);

	return it->second->getCheckpoint(_checkpointName).getMark() * 0.6;
}

/*****************************************************************************/

void Controller::addStudent(const std::string & _fullName)
{
	if (_fullName.empty())
		throw std::logic_error(Messages::EmptyStudentName);

	auto it = m_students.find(_fullName);
	if (it != m_students.end())
		throw std::logic_error(Messages::DuplicateStudent);

	m_students.insert(std::make_pair(_fullName, std::make_unique<Student>(_fullName)));
}

/*****************************************************************************/

void Controller::addStudentCheckpoint(
	const std::string & _fullName,
	const std::string & _courseName,
	const std::string & _checkpointName,
	int _mark
)
{
	auto it1 = m_courses.find(_courseName);
	if (it1 == m_courses.end())
		throw std::logic_error(Messages::CourseCannotBeFound);

	if (!it1->second->hasCheckpoint(_checkpointName))
		throw std::logic_error(Messages::CheckpointCannotBeFound);

	auto it2 = m_students.find(_fullName);
	if (it2 == m_students.end())
		throw std::logic_error(Messages::StudentCannotBeFound);

	if (_mark < 0 || _mark > getCheckpointMaxMark(_courseName, _checkpointName))
		throw std::logic_error(Messages::InvalidMarkValue);

	it2->second->addControlCheckpoint(it1->second->getCheckpoint(_checkpointName), _mark);
}

/*****************************************************************************/

int Controller::getStudentCheckpointMark(
	const std::string & _fullName,
	const std::string & _courseName,
	const std::string & _checkpointName
)
{
	auto it1 = m_courses.find(_courseName);
	if (it1 == m_courses.end())
		throw std::logic_error(Messages::CourseCannotBeFound);

	if (!it1->second->hasCheckpoint(_checkpointName))
		throw std::logic_error(Messages::CheckpointCannotBeFound);

	auto it2 = m_students.find(_fullName);
	if (it2 == m_students.end())
		throw std::logic_error(Messages::StudentCannotBeFound);


	return it2->second->isStudentPassCheckpoint(_checkpointName)
		 ? it2->second->getCheckpointMark(_checkpointName)
		 : 0;
}

/*****************************************************************************/

std::vector<std::string> Controller::getStudentsPermittedForExams() const
{
	std::vector<std::string> result;

	int totalMark, nCourses, nTests = 0;
	
	for (auto const & course : m_courses)
		if (course.second->getCourseControlForm() == ControlForm::Test)
			nTests++;

	for (auto const & student : m_students)
	{
		nCourses = 0;
		for (auto const & course : m_courses)
		{
			totalMark = 0;
			if (course.second->getCourseControlForm() == ControlForm::Test)
				student.second->forEachCheckpoint(
					[&](Checkpoint const & _c)
			{
				if (course.second->hasCheckpoint(_c.getName()))
					totalMark += student.second->getCheckpointMark(_c.getName());
			}
			);
			if (totalMark >= course.second->getCheckpointSum() * 0.6)
				nCourses++;
		}
		if (nCourses == nTests)
			result.push_back(student.first);
	};
		
	std::sort(result.begin(), result.end());

	return result;
}

/*****************************************************************************/

std::vector<std::string> Controller::getCoursesWithEveryonePassed() const
{
	std::vector<std::string> result;
	int total, nPassed;

	for (auto const & course : m_courses)
	{
		nPassed = 0;
		for (auto const & student : m_students)
		{
			total = 0;
			student.second->forEachCheckpoint(
				[&](Checkpoint const & _c)
			{
				if (course.second->hasCheckpoint(_c.getName()))
					total += student.second->getCheckpointMark(_c.getName());
			}
			);
			if (total >= course.second->getCheckpointSum() * 0.6)
				nPassed++;
		}
		if (nPassed == m_students.size())
			result.push_back(course.first);
	}

	std::sort(result.begin(), result.end());

	return result;
}

/*****************************************************************************/

std::vector<std::pair<std::string, double>> 
Controller::getAverageScoreByCourse() const
{
	std::vector<std::pair<std::string, double>> result;

	double total;
	int nPassed;

	for (auto const & course : m_courses)
	{
		nPassed = 0;
		total = 0;
		for (auto const & student : m_students)
		{
			student.second->forEachCheckpoint(
				[&](Checkpoint const & _c)
			{
				if (course.second->hasCheckpoint(_c.getName()))
					total += student.second->getCheckpointMark(_c.getName());
			}
			);
		}
		result.push_back(std::make_pair(course.first, total / m_students.size()));
	}

	std::sort(
		result.begin(),
		result.end(),
		[&](std::pair<std::string,double> const & _lhs, 
			std::pair<std::string,double> const & _rhs)
	{
		return _lhs.first < _rhs.first;
	}
	);

	return result;
}

/*****************************************************************************/

std::string Controller::getStudentWithBestAverageScore() const
{
	std::string bestStudent;

	int total;
	double totalMarks,max = 0;
	for (auto const & student : m_students)
	{
		totalMarks = 0;
		for (auto const & course : m_courses)
		{
			total = 0;
			student.second->forEachCheckpoint(
				[&](Checkpoint const & _c)
			{
				if (course.second->hasCheckpoint(_c.getName()))
					total += student.second->getCheckpointMark(_c.getName());
			}
			);
			totalMarks += total;
		}
		totalMarks /= m_courses.size();
		if (totalMarks >= max)
		{
			max = totalMarks;
			bestStudent = student.first; 
		}
	}

	return bestStudent;
}

/*****************************************************************************/
