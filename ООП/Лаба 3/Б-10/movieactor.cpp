// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "movieactor.hpp"
#include "messages.hpp"
#include "movie.hpp"

/*****************************************************************************/

// TODO implement your methods here

/*****************************************************************************/

MovieActor::MovieActor(
	std::string const & _name,
	int _year
)
	: m_name(_name)
	, m_year(_year)
{}

bool MovieActor::hasMovie(std::string const & _m) const
{
	return m_movies.find(_m) != m_movies.end();
}

void MovieActor::removeMovie(std::string const & _m)
{
	m_movies.erase(_m);
}

void MovieActor::forEachMovie(std::function<void(Movie const&_m)> _f) const
{
	for (auto const & m : m_movies)
		_f(*m.second);
}

void MovieActor::addMovie(Movie const & _m)
{
	m_movies.insert(std::make_pair(_m.getName(), &_m));
}
