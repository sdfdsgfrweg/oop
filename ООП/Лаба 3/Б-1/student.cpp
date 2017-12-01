// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "student.hpp"
#include "messages.hpp"

/*****************************************************************************/

Student::Student(
	int _ID,
	std::string const & _name,
	Date _date,
	StudyForm _form
)
	: m_ID(_ID)
	, m_name(_name)
	, m_birthDate(_date)
	, m_form(_form)
{}

/*****************************************************************************/
