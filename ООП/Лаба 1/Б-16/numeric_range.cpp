// (C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "numeric_range.hpp"

#include <stdexcept>

NumericRange::Iterator::Iterator(int _pos)
{
	m_currPos = _pos;
}

//�������� �������������
int NumericRange::Iterator::operator*() const
{
	return m_currPos;
}

bool NumericRange::Iterator::operator==(Iterator _iter) const
{
	return _iter.m_currPos == m_currPos;
}

bool NumericRange::Iterator::operator!=(Iterator _iter) const
{
	return !(_iter == *this);
}

//�������� ������������ ����������
NumericRange::Iterator & NumericRange::Iterator::operator++()
{
	NumericRange::Iterator _new = *this;
	m_currPos++;
	return _new;
}

//�������� ����������� ����������
NumericRange::Iterator NumericRange::Iterator::operator++(int)
{
	m_currPos++;
	return * this;
}

//����������� �� ���������
NumericRange::NumericRange()
{
	m_highBound = m_lowBound = 0;
}

//����������� � �����������
NumericRange::NumericRange(
	int _l,
	int _h
)
{
	m_lowBound = _l;
	m_highBound = _h;
	if (m_lowBound > m_highBound)
		throw std::logic_error("Low bound higher than high bound");
}

//����������� �� ������
NumericRange::NumericRange(std::string const & _s)
{
	//���������� ��� ����� � ������ ������� ���������
	std::string l, h;
	
	//������������� ��������� ������� � std::string::find , �������
	//���� ��������� ��������/������ � ���������� ������ , � ��������� ������
	//���������� -1

	if (_s.find("[") == std::string::npos) 
		throw std::logic_error("Invalid format");
	if (_s.find("]") == std::string::npos)
		throw std::logic_error("Invalid format");
	if (_s.find(":") == std::string::npos) 
		throw std::logic_error("Invalid format");
	
	//�������� �� ��, ��� � ��� � ������ ������� ������ �� ������ ����������
	//���������� ������ � ���������
	int lBr = 0,
		rBr = 0,
		dots = 0;

	for (int i = 0; i < _s.length(); i++)
	{
		if (_s[i] == '[')
			lBr++;
		if (_s[i] == ']')
			rBr++;
		if (_s[i] == ':')
			dots++;
	}

	//���� ������ 1 , �� ����������� ����������
	if (lBr > 1 || rBr > 1 || dots > 1)
		throw std::logic_error("Invalid format");

	//�������� ��������� �����
	bool isDots = false;
	for (int i = 1; i < _s.length() - 1; i++)
	{
		//���� ����� �� �����������, �� �������� ��������� ������ �������
		if (_s[i] == ':')
		{
			isDots = true;
			continue;
		}

		//���������� �������� 
		if (isDots)
			h += _s[i];
		else
			l += _s[i];
	}

	//�������� ������������ ��������� �� ��,
	//������������� �� ������ ������ � ����� ��� ���
	if (!std::atoi(l.c_str()))
		throw std::logic_error("Invalid format");
	if (!std::atoi(h.c_str())) 
		throw std::logic_error("Invalid format");

	//���� �� , �� �����������
	m_lowBound = std::atoi(l.c_str());
	m_highBound = std::atoi(h.c_str());
	if (m_lowBound > m_highBound)
		throw std::logic_error("Low bound higher than high bound");
}

std::ostream & operator<<(std::ostream & _s, NumericRange const & _nr)
{
	//���������� �������� ������ � �����
	_s << "[" << _nr.getLowBound() << ":" << _nr.getHighBound() << "]";
	return _s;
}