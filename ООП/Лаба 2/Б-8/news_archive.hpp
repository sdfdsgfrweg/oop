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

/*****************************************************************************/

class NewsArchive
{

	/*-----------------------------------------------------------------*/

public:

	struct New
	{
		std::string m_title;
		std::string m_detailText;
		
		New() = default;
		New(
			std::string const & _title,
			std::string const & _detailText
		)
			: m_title(_title)
			, m_detailText(_detailText)
		{}

		bool operator < (New const & _n) const
		{
			return m_title < _n.m_title;
		}
	};

	/*-----------------------------------------------------------------*/

		typedef
		std::function< void(DateTime, const std::string &, const std::string &) >
		EntryHandler;
	/*-----------------------------------------------------------------*/

	NewsArchive() = default;

	int getEntriesCount() const;

	bool  hasEntry(DateTime const & _time) const;

	bool  hasEntry(std::string const & _title) const;

	std::string const & getEntryTitle(DateTime const & _title) const;
	
	std::string const & getEntryText(DateTime const & _title) const;

	std::string const & getEntryText(std::string const & _title) const;

	DateTime const & getEntryDate(std::string const & _title) const;

	void forEachEntry(std::function<void(
		DateTime const &,
		std::string const &,
		std::string const &
		)> _function
	) const;

	void addEntry(
		DateTime const & _date,
		std::string const & _title,
		std::string const & _text
	);

	void modifyEntryTitle(
		DateTime const & _date,
		std::string const & _newTitle
	);

	void modifyEntryText(
		DateTime const & _date,
		std::string const & _newText
	);

	void modifyEntryText(
		std::string const & _title,
		std::string const & _newText
	);

	void removeEntry(DateTime const & _date);

	void removeEntry(std::string const & _date);

	std::vector<std::string> const getEntryTitlesWithTextContains(std::string const & _fragment) const;

	/*-----------------------------------------------------------------*/
	
private:

	/*-----------------------------------------------------------------*/
	std::map<DateTime, New> m_news;
	std::map<std::string, DateTime> m_newslog;
	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif // _NEWS_ARCHIVE_HPP_