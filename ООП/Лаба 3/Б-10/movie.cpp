// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "movie.hpp"
#include "messages.hpp"
#include "movieactor.hpp"

/*****************************************************************************/

// TODO implement your methods here

/*****************************************************************************/

Movie::Movie(
	std::string const & _name,
	int _year,
	int _rate
)
	: m_name(_name)
	, m_year(_year)
	, m_rate(_rate)
{}

void Movie::forEachGenre(std::function<void(std::string const&_g)> _f) const
{
	for (auto const & g : m_genres)
		_f(g);
}

void Movie::forEachActor(std::function<void(MovieActor const&_a)> _f) const
{
	for (auto const & a : m_actors)
		_f(*a.second);
}

void Movie::addGenre(std::string const & _g)
{
	m_genres.insert(_g);
}

void Movie::removeGenre(std::string const & _g)
{
	m_genres.erase(_g);
}

bool Movie::hasGenre(std::string const & _g) const
{
	return m_genres.find(_g) != m_genres.end();
}

void Movie::addActor(MovieActor const & _a)
{
	m_actors.insert(std::make_pair(_a.getName(), &_a));
}

void Movie::removeActor(std::string const & _a)
{
	m_actors.erase(_a);
}

bool Movie::hasActor(std::string const & _a) const
{
	return m_actors.find(_a) != m_actors.end();
}
