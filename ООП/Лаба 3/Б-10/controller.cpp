// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "movie.hpp"
#include "movieactor.hpp"

#include <algorithm>

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::createActor(std::string const & _actorName, int _birthYear)
{
	if (m_actors.find(_actorName) != m_actors.end())
		throw std::logic_error(Messages::ActorAlreadyRegistered);

	if (_actorName.empty())
		throw std::logic_error(Messages::ActorNameEmpty);

	if (_birthYear > 2017)
		throw std::logic_error(Messages::ActorBornInFuture);

	m_actors.insert(std::make_pair(_actorName, std::make_unique<MovieActor>(_actorName,_birthYear)));

}

/*****************************************************************************/

int Controller::getActorBirthYear(std::string const & _actorName) const
{
	if (m_actors.find(_actorName) == m_actors.end())
		throw std::logic_error(Messages::ActorUnresolved);

	return m_actors.find(_actorName)->second->getYear();
}

/*****************************************************************************/

void Controller::createMovie(std::string const & _movieTitle, int _productionYear, int _rating)
{
	if (m_movies.find(_movieTitle) != m_movies.end())
		throw std::logic_error(Messages::MovieAlreadyRegistered);

	if (_movieTitle.empty())
		throw std::logic_error(Messages::MovieTitleEmpty);

	if (_rating < 1 || _rating > 10)
		throw std::logic_error(Messages::RatingOutOfRange);

	if (_productionYear > 2017)
		throw std::logic_error(Messages::MovieProducedInFuture);

	m_movies.insert(std::make_pair(_movieTitle, std::make_unique<Movie>(_movieTitle, _productionYear, _rating)));
}

/*****************************************************************************/

int Controller::getMovieProductionYear(std::string const & _movieTitle) const
{
	if (m_movies.find(_movieTitle) == m_movies.end())
		throw std::logic_error(Messages::MovieUnresolved);

	return m_movies.find(_movieTitle)->second->getYear();
}

/*****************************************************************************/

int Controller::getMovieRating(std::string const & _movieTitle) const
{
	if (m_movies.find(_movieTitle) == m_movies.end())
		throw std::logic_error(Messages::MovieUnresolved);

	return m_movies.find(_movieTitle)->second->getRate();
}

/*****************************************************************************/

void Controller::addMovieGenre(std::string const & _movieTitle, std::string const & _genre)
{
	if (m_movies.find(_movieTitle) == m_movies.end())
		throw std::logic_error(Messages::MovieUnresolved);

	if (_genre.empty())
		throw std::logic_error(Messages::GenreNameEmpty);

	if (m_movies.find(_movieTitle)->second->hasGenre(_genre))
		throw std::logic_error(Messages::MovieGenreAlreadyAdded);

	m_movies.find(_movieTitle)->second->addGenre(_genre);
}

/*****************************************************************************/

std::vector<std::string> Controller::getMovieGenres(std::string const & _movieTitle) const
{
	if (m_movies.find(_movieTitle) == m_movies.end())
		throw std::logic_error(Messages::MovieUnresolved);

	std::vector<std::string> genres;

	m_movies.find(_movieTitle)->second->forEachGenre(
		[&](std::string const & _g)
	{
		genres.push_back(_g);
	});

	return genres;
}

/*****************************************************************************/

std::vector<std::string> Controller::getGenreMovies(std::string const & _genre) const
{
	if (_genre.empty())
		throw std::logic_error(Messages::GenreNameEmpty);

	std::vector<std::string> movies;

	for (auto const & m : m_movies)
		if (m.second->hasGenre(_genre))
			movies.push_back(m.first);

	std::sort(movies.begin(), movies.end());

	return movies;
}

/*****************************************************************************/

void Controller::addMovieActor(std::string const & _movieTitle, std::string const & _actorName)
{
	if (m_movies.find(_movieTitle) == m_movies.end())
		throw std::logic_error(Messages::MovieUnresolved);

	if (m_actors.find(_actorName) == m_actors.end())
		throw std::logic_error(Messages::ActorUnresolved);

	if (m_movies.find(_movieTitle)->second->hasActor(_actorName))
		throw std::logic_error(Messages::MovieActorAlreadyAdded);

	m_movies.find(_movieTitle)->second->addActor(*m_actors.find(_actorName)->second.get());
	m_actors.find(_actorName)->second->addMovie(*m_movies.find(_movieTitle)->second.get());
}

/*****************************************************************************/

std::vector<std::string> Controller::getMovieActors(std::string const & _movieTitle) const
{
	if (m_movies.find(_movieTitle) == m_movies.end())
		throw std::logic_error(Messages::MovieUnresolved);

	std::vector<std::string> actors;

	m_movies.find(_movieTitle)->second->forEachActor(
		[&](MovieActor const & _a)
	{
		actors.push_back(_a.getName());
	});

	sort(actors.begin(), actors.end());

	return actors;
}

/*****************************************************************************/

std::vector<std::string> Controller::getActorMovies(std::string const & _actorName) const
{
	if (m_actors.find(_actorName) == m_actors.end())
		throw std::logic_error(Messages::ActorUnresolved);

	std::vector<std::string> movies;

	m_actors.find(_actorName)->second->forEachMovie(
		[&](Movie const & _m)
	{
		movies.push_back(_m.getName());
	});

	std::sort(movies.begin(), movies.end());

	return movies;
}

/*****************************************************************************/

std::string Controller::getOldestMovieOfGenre(std::string const & _genre) const
{
	if (_genre.empty())
		throw std::logic_error(Messages::GenreNameEmpty);

	std::string oldestGenreMovie;
	int min = 2017;

	for (auto const & m : m_movies)
		if (m.second->hasGenre(_genre))
			if (m.second->getYear() < min)
			{
				min = m.second->getYear();
				oldestGenreMovie = m.first;
			}


	return oldestGenreMovie;
}

/*****************************************************************************/

double Controller::getActorAverageRating(std::string const & _actorName) const
{
	double totalRating = 0.0, filmCount = 0;

	if (m_actors.find(_actorName) == m_actors.end())
		throw std::logic_error(Messages::ActorUnresolved);

	for (auto const & m : m_movies)
		if (m.second->hasActor(_actorName))
		{
			totalRating += m.second->getRate();
			filmCount++;
		}

	return filmCount == 0 ? 0.0 : totalRating / filmCount;
}

/*****************************************************************************/

std::vector<std::string> Controller::getActorsThatNeverPlayedInGenre(std::string const & _genre) const
{
	if (_genre.empty())
		throw std::logic_error(Messages::GenreNameEmpty);
	
	std::vector<std::string> actors;
	bool isAct;
	for (auto const & a : m_actors)
	{
		isAct = false;
		a.second->forEachMovie(
			[&](Movie const & _m)
		{
			if (_m.hasGenre(_genre))
			{
				isAct = true;
				return;
			}
		});

		if (!isAct)
			actors.push_back(a.first);
	}
	
	std::sort(actors.begin(), actors.end());

	return actors;
}

/*****************************************************************************/

std::vector<std::string> Controller::getMoviesWhenActorWasYoungerThan(std::string const & _actorName, int _age) const
{
	if (m_actors.find(_actorName) == m_actors.end())
		throw std::logic_error(Messages::ActorUnresolved);

	if (_age < 1)
		throw std::logic_error(Messages::NegativeAge);
	
	std::vector<std::string> movies;
	
	for (auto const & m : m_movies)
		if (m.second->hasActor(_actorName))
			if ((m.second->getYear() - m_actors.find(_actorName)->second->getYear()) < _age)
				movies.push_back(m.first);

	std::sort(movies.begin(), movies.end());

	return movies;
}

/*****************************************************************************/
