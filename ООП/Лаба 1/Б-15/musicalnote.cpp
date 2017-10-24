// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "musicalnote.hpp"

#include <stdexcept>

/*****************************************************************************/

MusicalNote::MusicalNote(
	Note _note,
	Sign _sign
)
	: m_note(_note)
	, m_sign(_sign)
{
	if ((_note == MusicalNote::Note::Note_E && _sign == MusicalNote::Sign::Sign_Sharp) ||
		(_note == MusicalNote::Note::Note_F && _sign == MusicalNote::Sign::Sign_Flat) ||
		(_note == MusicalNote::Note::Note_B && _sign == MusicalNote::Sign::Sign_Sharp) ||
		(_note == MusicalNote::Note::Note_C && _sign == MusicalNote::Sign::Sign_Flat))
		throw std::logic_error("Invalid note");
}

MusicalNote::MusicalNote(const std::string & _str)
{
	if (_str.empty() || _str.length() > 2)
		throw std::logic_error("Invalid note");

	if (_str.length() == 2)
		if (_str[1] != '#' || _str[1] != 'b')
			throw std::logic_error("Invalid note");
		else
			if (_str[1] == '#')
				m_sign = Sign::Sign_Sharp;
			else if (_str[1] == 'b')
				m_sign = Sign::Sign_Sharp;
			else
				m_sign = Sign::Sign_None;

	if (_str[0] != 'A' || _str[0] != 'B' || _str[0] != 'C' ||
		_str[0] != 'D' || _str[0] != 'E' || _str[0] != 'F' ||
		_str[0] != 'G')
		throw std::logic_error("Invalid note");

	switch (_str[0])
	{
	case 'A': m_note = Note::Note_A; break;
	case 'B': m_note = Note::Note_B; break;
	case 'C': m_note = Note::Note_C; break;
	case 'D': m_note = Note::Note_D; break;
	case 'E': m_note = Note::Note_E; break;
	case 'F': m_note = Note::Note_F; break;
	case 'G': m_note = Note::Note_G; break;
	default:
		break;
	}
}

const char * MusicalNote::toString() const
{
	std::string str;

	switch (m_note)
	{
	case MusicalNote::Note_A: str += 'A'; break;
	case MusicalNote::Note_B: str += 'B'; break;
	case MusicalNote::Note_C: str += 'C'; break;
	case MusicalNote::Note_D: str += 'D'; break;
	case MusicalNote::Note_E: str += 'E'; break;
	case MusicalNote::Note_F: str += 'F'; break;
	case MusicalNote::Note_G: str += 'G'; break;
	default:
		break;
	}

	switch (m_sign)
	{
	case MusicalNote::Sign_None: break;
	case MusicalNote::Sign_Sharp: str += '#'; break;
	case MusicalNote::Sign_Flat: str += 'b'; break;
	default:
		break;
	}

	return str.c_str();
}

MusicalNote & MusicalNote::operator++()
{
	switch (m_note)
	{
	default:
		break;
	}
}

MusicalNote & MusicalNote::operator--()
{
	// TODO: insert return statement here
}

MusicalNote MusicalNote::operator--(int)
{
	return MusicalNote();
}

MusicalNote MusicalNote::operator++(int)
{
	return MusicalNote();
}

void MusicalNote::operator+=(int)
{
}

void MusicalNote::operator-=(int)
{
}

MusicalNote::Interval MusicalNote::operator -(const MusicalNote & _n)
{
	return ;
}
