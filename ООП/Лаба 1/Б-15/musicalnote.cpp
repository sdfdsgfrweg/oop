// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine
#define _CRT_SECURE_NO_WARNINGS
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
	checkMusicalNote(m_note, m_sign);
}

MusicalNote::MusicalNote(const std::string & _str)
{
	if (_str.empty() || _str.length() > 2)
		throw std::logic_error("Invalid format");

	if (_str.length() == 2)
		if (_str[1] == '#' || _str[1] == 'b')
			if (_str[1] == '#')
				m_sign = Sign::Sign_Sharp;
			else
				m_sign = Sign::Sign_Flat;
		else
			throw std::logic_error("Invalid format");
	else
		m_sign = Sign::Sign_None;

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
		throw std::logic_error("Invalid format");
	}

	checkMusicalNote(m_note, m_sign);
}

const char * MusicalNote::toString() const
{
	std::string str;
	char buffer[3];
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
	strcpy(buffer, str.c_str());
	return buffer;
}

MusicalNote & MusicalNote::operator++()
{
	switch (m_sign)
	{
	case MusicalNote::Sign_None:
		m_sign = MusicalNote::Sign_Sharp;
		break;
	case MusicalNote::Sign_Sharp:
		m_sign = MusicalNote::Sign_None;
		if (getNote() == MusicalNote::Note_G)
			m_note = MusicalNote::Note(MusicalNote::Note_A);
		else
			m_note = MusicalNote::Note(getNote() + 1);
		break;
	}
	if (!(checkMusicalNote(m_note, m_sign)))
		++*this;
	return *this;
}

MusicalNote & MusicalNote::operator--()
{
	switch (m_sign)
	{
	case MusicalNote::Sign_None:
		m_sign = MusicalNote::Sign_Sharp;
		break;
	case MusicalNote::Sign_Sharp:
		m_sign = MusicalNote::Sign_None;
		if (getNote() == MusicalNote::Note_A)
			m_note = MusicalNote::Note(MusicalNote::Note_G);
		else
			m_note = MusicalNote::Note(getNote() - 1);
		break;
	}
	if (!(checkMusicalNote(m_note, m_sign)))
		--*this;
	return *this;
}

MusicalNote MusicalNote::operator--(int)
{
	MusicalNote note(m_note,m_sign);
	switch (m_sign)
	{
	case MusicalNote::Sign_None:
		m_sign = MusicalNote::Sign_Sharp;
		break;
	case MusicalNote::Sign_Sharp:
		m_sign = MusicalNote::Sign_None;
		if (getNote() == MusicalNote::Note_A)
			m_note = MusicalNote::Note(MusicalNote::Note_G);
		else
			m_note = MusicalNote::Note(getNote() - 1);
		break;
	}
	if (!(checkMusicalNote(m_note, m_sign)))
		++*this;
	return note;
}

MusicalNote MusicalNote::operator++ (int)
{
	MusicalNote note(m_note, m_sign);
	switch (m_sign)
	{
	case MusicalNote::Sign_None:
		m_sign = MusicalNote::Sign_Sharp;
		break;
	case MusicalNote::Sign_Sharp:
		m_sign = MusicalNote::Sign_None;
		if (getNote() == MusicalNote::Note_G)
			m_note = MusicalNote::Note(MusicalNote::Note_A);
		else
			m_note = MusicalNote::Note(getNote() + 1);
		break;
	}
	if (!(checkMusicalNote(m_note, m_sign)))
		++*this;
	return note;
}

void MusicalNote::operator+=(int)
{
}

void MusicalNote::operator-=(int)
{
}

MusicalNote::Interval MusicalNote::operator -(const MusicalNote & _n)
{
	return MusicalNote::Interval::Interval_Fifth;
}

bool MusicalNote::checkMusicalNote(Note _note, Sign _sign) const
{
	if ((_note == MusicalNote::Note::Note_E && _sign == MusicalNote::Sign::Sign_Sharp) ||
		(_note == MusicalNote::Note::Note_F && _sign == MusicalNote::Sign::Sign_Flat) ||
		(_note == MusicalNote::Note::Note_B && _sign == MusicalNote::Sign::Sign_Sharp) ||
		(_note == MusicalNote::Note::Note_C && _sign == MusicalNote::Sign::Sign_Flat))
		throw std::logic_error("Invalid note");
	return true;
}
