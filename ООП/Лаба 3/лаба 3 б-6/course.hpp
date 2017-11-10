// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _COURSE_HPP_
#define _COURSE_HPP_

/*****************************************************************************/

class Checkpoint;

/*****************************************************************************/

#include "controlform.hpp"

#include <string>
#include <memory>
#include <unordered_map>
#include <functional>

class Course
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Course(
		std::string const & _courseName,
		ControlForm _form
	);

	~Course() = default;

	void addCheckpoint(std::unique_ptr<Checkpoint> _c);

	std::string const & getCourseName() const;

	ControlForm getCourseControlForm() const;

	bool hasCheckpoints() const;

	bool hasCheckpoint(std::string const & _c) const;

	void forEachCheckpoint(std::function<void(Checkpoint const &)> _f) const;

	Checkpoint & getCheckpoint(std::string const & _c) const;

	int getCheckpointSum() const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::string m_courseName;
	ControlForm m_form;
	std::unordered_map<std::string,std::unique_ptr<Checkpoint> > m_checkpoints;

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

inline
std::string const &
Course::getCourseName() const
{
	return m_courseName;
}

/*****************************************************************************/

inline
ControlForm Course::getCourseControlForm() const
{
	return m_form;
}

/*****************************************************************************/

inline
bool Course::hasCheckpoints() const
{
	return !m_checkpoints.empty();
}

/*****************************************************************************/

inline
Checkpoint & Course::getCheckpoint(std::string const & _c) const
{
	return *m_checkpoints.find(_c)->second.get();
}

/*****************************************************************************/

#endif // _COURSE_HPP_