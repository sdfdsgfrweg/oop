// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "checkpoint.hpp"

/*****************************************************************************/

Checkpoint::Checkpoint(
	std::string const & _name,
	int _mark
)
	: m_name(_name)
	, m_maxMark(_mark)
{}

/*****************************************************************************/