// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _STUDENT_HPP_
#define _STUDENT_HPP_

/*****************************************************************************/

class Checkpoint;

/*****************************************************************************/

#include <string>
#include <map>
#include <functional>

class Student
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Student(std::string const & _fullName);

	~Student();
	
	void addControlCheckpoint(Checkpoint & _c, int _mark);

	std::string const & getName() const;

	int getCheckpointMark(std::string const & _c);

	bool isStudentPassCheckpoint(std::string const & _c) const;

	void forEachCheckpoint(std::function<void(Checkpoint const & _e)> _f) const;


	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::string m_fullName;
	std::map<std::string,std::pair<Checkpoint *, int> > m_controlCheckpoints;

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

inline
std::string const &
Student::getName() const
{
	return m_fullName;
}

/*****************************************************************************/

inline
bool Student::isStudentPassCheckpoint(std::string const & _c) const
{
	return m_controlCheckpoints.find(_c) != m_controlCheckpoints.end();
}

/*****************************************************************************/

#endif // _STUDENT_HPP_