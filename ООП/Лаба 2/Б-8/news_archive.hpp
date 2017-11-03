// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _NEWS_ARCHIVE_HPP_
#define _NEWS_ARCHIVE_HPP_

/*****************************************************************************/

#include "datetime.hpp"

#include <string>
#include <functional>
#include <map>
#include <algorithm>
#include <vector>
#include <map>

class NewsArchive
{

public:

	typedef std::function< void(DateTime, const std::string &, const std::string &) > EntryHandler;

	NewsArchive() = default; //����������� �� ���������
	int getEntriesCount() const;//���������� ���������� �������
	bool hasEntry(DateTime date) const;//��������� ������ �� �������
	bool hasEntry(std::string title) const;//��������� ������ �� ���������
	std::string const & getEntryTitle(DateTime date) const; //��������� ��������� ������ �� �������
	std::string const & getEntryText(DateTime  date) const; //��������� ������ �� �������
	std::string const & getEntryText(std::string title) const;//��������� ������ �� ���������
	DateTime const & getEntryDate(std::string  title) const; //��������� ���� �� ���������
	void forEachEntry(EntryHandler _function) const; //����� ��� �������� �� �������
	void addEntry(DateTime date, std::string title,std::string _text); //���������� ������
	void removeEntry(std::string title); //�������� ������ �� ���������
	void modifyEntryTitle(DateTime date,std::string new_title);//��������������� ��������� �� ����
	void modifyEntryText(DateTime  date, std::string new_text); //��������������� ������ �� ����
	void modifyEntryText(std::string title,std::string new_text); //��������������� ������ �� ���������
	void removeEntry(DateTime date); //�������� ������ �� ����
	std::vector<std::string> const getEntryTitlesWithTextContains(std::string frag) const; //������� ������� �� �������� ������� �������� ���������
	
	struct New
	{
		std::string m_title;
		std::string m_text;

		New() = default;
		New(std::string title, std::string _text)
			: m_title(title), m_text(_text)
		{}
		bool operator < (New _new) const;
	};

private:
	std::map<DateTime, New> news;
	std::map<std::string, DateTime> news_journal;
};

inline bool NewsArchive::New::operator < (New _n) const
{
	return m_title < _n.m_title;
}

#endif // _NEWS_ARCHIVE_HPP_