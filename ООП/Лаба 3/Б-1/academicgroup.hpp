// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _ACADEMICGROUP_HPP_
#define _ACADEMICGROUP_HPP_

#include <string>
#include <unordered_map>
#include <functional>

/*****************************************************************************/

class Student;

/*****************************************************************************/


class AcademicGroup
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	AcademicGroup(std::string const & _name);

	~AcademicGroup() = default;

	void addStudent(Student const & _s);

	void addMajorStudent(Student const & _ms);

	bool hasStudent(int _ID) const;

	bool hasMajorStudent() const;

	Student const & getStudent(int _ID) const;

	Student const & getMajorStudent() const;

	void forEachStudent(std::function<void(Student const & _s)> _f) const;

	std::string const & getName() const;

	void removeStudent(int _ID);

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string m_name;

	std::unordered_map<int, Student const *> m_students;

	Student const * m_majorStudent;

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
std::string const & AcademicGroup::getName() const
{
	return m_name;
}

/*****************************************************************************/

#endif // _ACADEMICGROUP_HPP_
