// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _MUSICALNOTE_HPP_
#define _MUSICALNOTE_HPP_

/*****************************************************************************/

#include <string>

class MusicalNote
{

/*-----------------------------------------------------------------*/

public:

/*------------------------------------------------------------------*/

	enum Note
	{
		Note_A,
		Note_B,
		Note_C,
		Note_D,
		Note_E,
		Note_F,
		Note_G
	};

	enum Sign
	{
		Sign_None,
		Sign_Sharp,
		Sign_Flat
	};

	enum Interval
	{
		Interval_Prime,
		Interval_Minor_Second,
		Interval_Major_Second,
		Interval_Minor_Third,
		Interval_Major_Third,
		Interval_Fourth,
		Interval_Small_Fifth,
		Interval_Fifth,
		Interval_Minor_Sixth,
		Interval_Major_Sixth,
		Interval_Minor_Seventh,
		Interval_Major_Seventh
	};

/*------------------------------------------------------------------*/

public:

	MusicalNote(
		Note _note,
		Sign _sign = Sign::Sign_None
	);
	
	MusicalNote(const std::string & _str);

	~MusicalNote() = default;

	Note getNote() const;

	Sign getSign() const;

	const char * toString() const;

	bool operator == (const MusicalNote & _note) const;

	bool operator != (const MusicalNote & _note) const;

	MusicalNote & operator ++ ();

	MusicalNote & operator -- ();

	MusicalNote operator -- (int);

	MusicalNote operator ++ (int);

	void operator += (int);

	void operator -= (int);

	Interval operator - (const MusicalNote & _n);

private:

	bool checkMusicalNote(Note _note, Sign _sign) const;

	Note m_note;

	Sign m_sign;

/*------------------------------------------------------------------*/

};

inline bool 
MusicalNote::operator == (const MusicalNote & _note) const
{
	int lhs = 0, rhs = 0;
	if (m_sign == MusicalNote::Sign::Sign_Flat)
		lhs -= 1;
	else if (m_sign == MusicalNote::Sign::Sign_Sharp)
		lhs += 1;
	if (_note.m_sign == MusicalNote::Sign::Sign_Flat)
		rhs -= 1;
	else if (_note.m_sign == MusicalNote::Sign::Sign_Sharp)
		rhs += 1; 
	lhs += getNote() * 2;
	rhs += _note.getNote() * 2;
	return lhs == rhs;
}

inline bool 
MusicalNote::operator != (const MusicalNote & _note) const
{
	return !(*this == _note);
}

inline
MusicalNote::Note MusicalNote::getNote() const
{
	return m_note;
}

inline
MusicalNote::Sign MusicalNote::getSign() const
{
	return m_sign;
}

/*****************************************************************************/

#endif //  _MUSICALNOTE_HPP_
