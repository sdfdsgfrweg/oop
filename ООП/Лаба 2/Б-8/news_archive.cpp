// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "news_archive.hpp"
#include "messages.hpp"
#include <iostream>
/*****************************************************************************/

int NewsArchive::getEntriesCount() const
{
	return m_news.size();
}

/*****************************************************************************/

bool NewsArchive::hasEntry(DateTime const & _time) const
{	
	return m_news.find(_time) != m_news.end();
}

/*****************************************************************************/

bool NewsArchive::hasEntry(std::string const & _title) const
{
	return m_newslog.find(_title) != m_newslog.end();
}

/*****************************************************************************/

std::string const & NewsArchive::getEntryTitle(DateTime const & _time) const
{
	auto it = m_news.find(_time);
	if (it == m_news.end())
		throw std::logic_error(Messages::EntryDoesNotExist);

	return it->second.m_title;
}

/*****************************************************************************/

std::string const & NewsArchive::getEntryText(DateTime const & _time) const
{
	auto it = m_news.find(_time);
	if (it == m_news.end())
		throw std::logic_error(Messages::EntryDoesNotExist);

	return it->second.m_detailText;
}

/*****************************************************************************/

std::string const & NewsArchive::getEntryText(std::string const & _title) const
{
	auto it = m_newslog.find(_title);
	if (it == m_newslog.end())
		throw std::logic_error(Messages::EntryDoesNotExist);

	return m_news.find(it->second)->second.m_detailText;
}

/*****************************************************************************/

DateTime const & NewsArchive::getEntryDate(std::string const & _title) const
{
	auto it = m_newslog.find(_title);
	if (it == m_newslog.end())
		throw std::logic_error(Messages::EntryDoesNotExist);

	return it->second;
}

/*****************************************************************************/

void NewsArchive::forEachEntry(std::function<void(
	DateTime const & _time,
	std::string const & _title,
	std::string const & _text)>
	_function) const
{
	for (auto eachNew : m_news)
		_function(
			eachNew.first,
			eachNew.second.m_title,
			eachNew.second.m_detailText
		);
}

/*****************************************************************************/

void NewsArchive::addEntry(
	DateTime const & _time,
	std::string const & _title,
	std::string const & _text
)
{
	if (_title.empty())
		throw std::logic_error(Messages::EmptyEntryTitle);

	if (_text.empty())
		throw std::logic_error(Messages::EmptyEntryText);	

	auto it1 = m_news.find(_time);

	auto it2 = m_newslog.find(_title);

	if (it1 != m_news.end() || it2 != m_newslog.end())
		throw std::logic_error(Messages::DuplicatedEntry);
	
	m_news.insert(std::make_pair(_time, New(_title,_text)));
	m_newslog.insert(std::make_pair(_title,_time));
}

/*****************************************************************************/

void NewsArchive::modifyEntryTitle(
	DateTime const & _time,
	std::string const & _newTitle
)
{
	if (_newTitle.empty())
		throw std::logic_error(Messages::EmptyEntryTitle);

	auto it1 = m_news.find(_time);
	if (it1 == m_news.end())
		throw std::logic_error(Messages::EntryDoesNotExist);

	m_newslog.erase(it1->second.m_title);
	it1->second.m_title = _newTitle;
	m_newslog.insert(std::make_pair(_newTitle, _time));
}

/*****************************************************************************/

void NewsArchive::modifyEntryText(
	DateTime const & _time,
	std::string const & _newText
)
{
	if (_newText.empty())
		throw std::logic_error(Messages::EmptyEntryText);

	auto it = m_news.find(_time);
	if (it == m_news.end())
		throw std::logic_error(Messages::EntryDoesNotExist);

	it->second.m_detailText = _newText;
}

/*****************************************************************************/

void NewsArchive::modifyEntryText(
	std::string const & _title,
	std::string const & _newText
)
{
	if (_newText.empty())
		throw std::logic_error(Messages::EmptyEntryText);

	auto it1 = m_newslog.find(_title);
	if (it1 == m_newslog.end())
		throw std::logic_error(Messages::EntryDoesNotExist);

	m_news.find(it1->second)->second.m_detailText = _newText;
}

/*****************************************************************************/

void NewsArchive::removeEntry(DateTime const & _time)
{
	auto it = m_news.find(_time);
	if (it == m_news.end())
		throw std::logic_error(Messages::EntryDoesNotExist);

	m_newslog.erase(m_newslog.find(it->second.m_title));
	m_news.erase(it->first);
}

/*****************************************************************************/

void NewsArchive::removeEntry(std::string const & _title)
{
	auto it = m_newslog.find(_title);
	if (it == m_newslog.end())
		throw std::logic_error(Messages::EntryDoesNotExist);

	m_news.erase(it->second);
	m_newslog.erase(it);
}

/*****************************************************************************/

std::vector<std::string> const
NewsArchive::getEntryTitlesWithTextContains(std::string const & _fragment) const
{
	auto vec = m_news;
	std::vector<std::string> titles;

	int fragIndex;
	for (auto eachNew : m_news)
	{
		fragIndex = 0;
		for (int i = 0; i < eachNew.second.m_detailText.size(); i++)
		{
			(_fragment[fragIndex] == eachNew.second.m_detailText[i]) ? fragIndex++ : fragIndex = 0;
			
			if (fragIndex == _fragment.size())
				break;
		}

		if (fragIndex == _fragment.size() || _fragment.empty())
			titles.push_back(eachNew.second.m_title);
	}

	return titles;
}

/*****************************************************************************/