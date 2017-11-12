// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _DATETIME_HPP_
#define _DATETIME_HPP_

/*****************************************************************************/


class DateTime
{

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	DateTime();
	DateTime( int _year, int _month, int _day, int _hours, int _minutes, int _seconds );
	// Format: YYYY/MM/DD-H:M:S
	DateTime( const char* _datetime, char _datesep = '/', char _datetimesep = '-', char _timesep = ':' );

	int getYear() const;
	int getMonth() const;
	int getDay() const;
	int getHours() const;
	int getMinutes() const;
	int getSeconds() const;

	bool isLeapYear() const;

	bool operator == ( DateTime _d ) const;
	bool operator != ( DateTime _d ) const;
	bool operator < ( DateTime _d ) const;
	bool operator <= ( DateTime _d ) const;
	bool operator > ( DateTime _d ) const;
	bool operator >= ( DateTime _d ) const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	bool isValid() const;

	/*-----------------------------------------------------------------*/

	int m_year, m_month, m_day, m_hours, m_minutes, m_seconds;

	/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

#endif // _DATETIME_HPP_
