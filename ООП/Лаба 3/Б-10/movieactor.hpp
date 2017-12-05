// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MOVIEACTOR_HPP_
#define _MOVIEACTOR_HPP_

/*****************************************************************************/

#include <string>
#include <unordered_map>
#include <functional>

/*****************************************************************************/

class Movie;

/*****************************************************************************/


class MovieActor
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	MovieActor(
		std::string const & _name,
		int _year
	);

	~MovieActor() = default;

	int getYear() const;

	std::string const & getName() const;

	void addMovie(Movie const & _m);

	bool hasMovie(std::string const & _m) const;

	void removeMovie(std::string const & _m);

	void forEachMovie(std::function<void(Movie const & _m)> _f)const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string m_name;

	int m_year;

	std::unordered_map<std::string, Movie const *> m_movies;

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
int MovieActor::getYear() const
{
	return m_year;
}

/*****************************************************************************/

inline
std::string const & MovieActor::getName() const
{
	return m_name;
}

/*****************************************************************************/

#endif //  _MOVIEACTOR_HPP_
