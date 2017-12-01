// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "academicgroup.hpp"
#include "messages.hpp"
#include "student.hpp"

/*****************************************************************************/

void AcademicGroup::removeStudent(int _ID)
{
	m_students.erase(_ID);
}

/*****************************************************************************/

AcademicGroup::AcademicGroup(std::string const & _name)
	: m_name(_name)
{}

/*****************************************************************************/

void AcademicGroup::addStudent(Student const & _s)
{
	m_students.insert(std::make_pair(_s.getID(), &_s));
}

/*****************************************************************************/

void AcademicGroup::addMajorStudent(Student const & _ms)
{
	m_majorStudent = &_ms;
}

/*****************************************************************************/

bool AcademicGroup::hasStudent(int _ID) const
{
	return m_students.find(_ID) != m_students.end();
}

/*****************************************************************************/

bool AcademicGroup::hasMajorStudent() const
{
	return m_majorStudent != nullptr;
}

/*****************************************************************************/

Student const & AcademicGroup::getStudent(int _ID) const
{
	return * m_students.find(_ID)->second;
}

/*****************************************************************************/

Student const & AcademicGroup::getMajorStudent() const
{
	return *m_majorStudent;
}

/*****************************************************************************/

void AcademicGroup::forEachStudent(std::function<void(Student const&_s)> _f) const
{
	for (auto const & s : m_students)
		_f(*s.second);
}

/*****************************************************************************/
