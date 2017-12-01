// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _STUDENT_HPP_
#define _STUDENT_HPP_

/*****************************************************************************/

#include "date.hpp"
#include "studyform.hpp"

#include <string>

class Student
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Student(
		int _ID,
		std::string const & _name,
		Date _date,
		StudyForm _form
	);

	~Student() = default;

	int getID() const;

	std::string const & getName() const;

	Date getBirthDay() const;

	StudyForm getStudyForm() const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	int m_ID;

	std::string m_name;

	Date m_birthDate;

	StudyForm m_form;

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
int Student::getID() const
{
	return m_ID;
}

/*****************************************************************************/

inline
std::string const & Student::getName() const
{
	return m_name;
}

/*****************************************************************************/

inline
Date Student::getBirthDay() const
{
	return m_birthDate;
}

/*****************************************************************************/

inline
StudyForm Student::getStudyForm() const
{
	return m_form;
}

/*****************************************************************************/

#endif // _STUDENT_HPP_
