// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "date.hpp"
#include "studyform.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

/*****************************************************************************/

class Student;
class AcademicGroup;

class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	~Controller ();

	Controller ( const Controller & ) = delete;
	Controller & operator = ( const Controller & ) = delete;

/*-----------------------------------------------------------------*/

	void createStudent (
		int _studentId,
		const std::string & _fullName,
		Date _birthday,
		StudyForm _studyForm
	);

	const std::string & getStudentName ( int _studentId ) const;

	Date getStudentBirthday ( int _studentId ) const;

	StudyForm getStudentStudyForm ( int _studentId ) const;

/*-----------------------------------------------------------------*/

	void createGroup ( const std::string & _groupName );

	void addStudentToGroup ( int _studentId, const std::string & _groupName );

	void removeStudentFromGroup ( int _studentId, const std::string & _groupName );

	std::vector< int > getStudentIdsOfGroup ( const std::string & _groupName ) const;

	void assignGroupCaptain ( int _studentId, const std::string & _groupName );

	int getGroupCaptainId ( const std::string & _groupName ) const;

/*-----------------------------------------------------------------*/

	int getStudentsCountPerStudyForm ( StudyForm _studyForm ) const;

	double getBudgetStudentsPercentageInGroup ( std::string const & _groupName ) const;

	std::vector< int > getStudentsBornFirstDayOfMonth () const;

	std::string getEldestCaptainName () const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/
	
	std::unordered_map<std::string, std::unique_ptr<AcademicGroup>> m_groups;

	std::unordered_map<int, std::unique_ptr<Student>> m_students;

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

#endif //  _CONTROLLER_HPP_
