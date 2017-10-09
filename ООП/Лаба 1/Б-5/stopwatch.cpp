// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "stopwatch.hpp"

#include <stdexcept>

/*****************************************************************************/

Stopwatch::Stopwatch(clock_t _startTime)
	: m_currentTime(_startTime)
	, m_isOnPause(true)
	, m_start(0)
{}

void Stopwatch::pause()
{
	if (m_isOnPause)
		throw std::logic_error("Stopwatch is paused already");
	else
		m_isOnPause = true;

	//фиксируем время паузы
	clock_t finishPt = clock();
	m_currentTime = finishPt;
}

void Stopwatch::reset()
{
	m_currentTime = 0;
	m_start = 0;
	m_isOnPause = true;
}

void Stopwatch::resume()
{
	if (!m_isOnPause)
		throw std::logic_error("Stopwatch is not paused");
	else
		m_isOnPause = false;

	//если не было пауз, то фиксируем начальное время
	if (m_currentTime == 0) m_start = clock();
}

bool Stopwatch::isPaused() const
{
	return m_isOnPause;
}

clock_t Stopwatch::getElapsed() const
{
	//фиксируем конечное время
	clock_t finishPt = clock();
	
	//если добавляли время сразу
	if (m_currentTime && !m_start) return m_currentTime;
	//если была пауза , возобновление без стопа
	if (m_currentTime && !m_isOnPause) return finishPt - m_currentTime;
	//если была пауза
	if (m_currentTime) return m_currentTime - m_start;
	//если не было засечения
	if (m_isOnPause && !m_currentTime) return 0;

	//если не было паузы и время идет
	return finishPt - m_start;
}

Stopwatch Stopwatch::operator +(int  _rhs)
{
	return Stopwatch(_rhs + m_currentTime);
}

void Stopwatch::operator +=(int  _rhs)
{
	m_currentTime += _rhs;
}

Stopwatch Stopwatch::operator -(int _rhs)
{
	return Stopwatch(m_currentTime - _rhs);
}

void Stopwatch::operator -=(int _rhs)
{
	m_currentTime -= _rhs;
}

int Stopwatch::getElapsedMinutes() const
{
	clock_t time = getElapsed();
	return (time - (getElapsedHours() * 3600000)) / 60000;
}

int Stopwatch::getElapsedSeconds() const
{
	clock_t time = getElapsed();

	return (time - (getElapsedHours() * 3600000) - (getElapsedMinutes() * 60000)) / 1000;
}

int Stopwatch::getElapsedHours() const
{
	clock_t time = getElapsed();
	return time / 3600000;
}

void Stopwatch::display(std::ostream & _s)
{
	_s << getElapsedHours() << ":" << getElapsedMinutes() << ":"
		<< getElapsedSeconds();
}

/*****************************************************************************/
