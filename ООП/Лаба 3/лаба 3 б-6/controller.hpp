// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "controlform.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

/*****************************************************************************/

class Checkpoint;
class Student;
class Course;

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

	void addCourse(
		const std::string & _courseName
		, ControlForm _controlForm
	);

	ControlForm getCourseControlForm(const std::string & _courseName) const;

	void validateCourseCheckpoints(const std::string & _courseName) const;

	/*-----------------------------------------------------------------*/

	void addCheckpoint(
		const std::string & _courseName
		, const std::string & _checkpointName
		, int _maxMark
	);

	int getCheckpointMaxMark(
		const std::string & _courseName
		, const std::string & _checkpointName
	) const;

	int getCheckpointMinMark(
		const std::string & _courseName
		, const std::string & _checkpointName
	) const;

	/*-----------------------------------------------------------------*/

	void addStudent(const std::string & _fullName);

	void addStudentCheckpoint(
		const std::string & _fullName
		, const std::string & _courseName
		, const std::string & _checkpointName
		, int _mark
	);

	int getStudentCheckpointMark(
		const std::string & _fullName
		, const std::string & _courseName
		, const std::string & _checkpointName
	);

	/*-----------------------------------------------------------------*/

	std::vector< std::string > getStudentsPermittedForExams() const;

	std::vector< std::string > getCoursesWithEveryonePassed() const;

	std::vector< std::pair< std::string, double > > getAverageScoreByCourse() const;

	std::string getStudentWithBestAverageScore() const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::unordered_map < std::string, std::unique_ptr<Course> > m_courses;
	std::unordered_map < std::string, std::unique_ptr<Student> > m_students;
	
	/*-----------------------------------------------------------------*/
};


/*****************************************************************************/

#endif // _CONTROLLER_HPP_