// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MOVIE_HPP_
#define _MOVIE_HPP_

/*****************************************************************************/

#include <string>
#include <set>
#include <functional>
#include <unordered_map>

/*****************************************************************************/

class MovieActor;

/*****************************************************************************/


class Movie
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Movie(
		std::string const & _name,
		int _year,
		int _rate
	);

	~Movie() = default;

	std::string const & getName() const;

	int getYear() const;

	int getRate() const;

	void forEachGenre(std::function<void(std::string const & _g)> _f) const;

	void forEachActor(std::function<void(MovieActor const & _a)> _f) const;

	void addGenre(std::string const & _g);

	void removeGenre(std::string const & _g);

	bool hasGenre(std::string const & _g) const;

	void addActor(MovieActor const & _a);

	void removeActor(std::string const & _a);

	bool hasActor(std::string const & _a) const;


/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string m_name;

	int m_year;

	int m_rate;

	std::set<std::string> m_genres;

	std::unordered_map<std::string, MovieActor const * > m_actors;

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
std::string const & Movie::getName() const
{
	return m_name;
}

/*****************************************************************************/

inline
int Movie::getYear() const
{
	return m_year;
}

/*****************************************************************************/

inline
int Movie::getRate() const
{
	return m_rate;
}

/*****************************************************************************/

#endif //  _MOVIE_HPP_
