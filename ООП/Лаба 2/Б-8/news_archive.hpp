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

	NewsArchive() = default; //конструктор по умолчанию
	int getEntriesCount() const;//возвращает количество записей
	bool hasEntry(DateTime date) const;//проверяет запись по времени
	bool hasEntry(std::string title) const;//проверяет запись по заголовку
	std::string const & getEntryTitle(DateTime date) const; //получение заголовка записи по времени
	std::string const & getEntryText(DateTime  date) const; //получение текста по времени
	std::string const & getEntryText(std::string title) const;//получение текста по заголовку
	DateTime const & getEntryDate(std::string  title) const; //получение даты по заголовку
	void forEachEntry(EntryHandler _function) const; //метод для проходки по записям
	void addEntry(DateTime date, std::string title,std::string _text); //добавление записи
	void removeEntry(std::string title); //удаление записи по заголовку
	void modifyEntryTitle(DateTime date,std::string new_title);//модифицирование заголовка по дате
	void modifyEntryText(DateTime  date, std::string new_text); //модифицирование текста по дате
	void modifyEntryText(std::string title,std::string new_text); //модифицирование текста по заголовку
	void removeEntry(DateTime date); //удаление записи по дате
	std::vector<std::string> const getEntryTitlesWithTextContains(std::string frag) const; //возврат массива со строками которые содержат фрагменты
	
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