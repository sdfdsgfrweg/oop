// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _STOPWATCH_HPP_
#define _STOPWATCH_HPP_

/*****************************************************************************/

#include <ctime>
#include <iostream>
#include <time.h>

/*****************************************************************************/


class Stopwatch
{

/*-----------------------------------------------------------------*/
public:
	Stopwatch(clock_t _startTime = 0);

	~Stopwatch() = default;

	void pause();

	void reset();

	void resume();

	bool isPaused() const;

	void display(std::ostream & _s);

	clock_t getElapsed() const;

	Stopwatch operator +(int _rhs);

	void operator +=(int _rhs);

	Stopwatch operator -(int _rhs);

	void operator -=(int  _rhs);

	int getElapsedMinutes() const;

	int getElapsedSeconds() const;

	int getElapsedHours() const;

private:

	clock_t m_start;
	clock_t m_currentTime;

	bool m_isOnPause;
	
/*------------------------------------------------------------------*/

};

/*****************************************************************************/

#endif //  _STOPWATCH_HPP_
