// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "news_archive.hpp"
#include "messages.hpp"
#include <iostream>

int NewsArchive::getEntriesCount() const
{
	return news.size();
}

bool NewsArchive::hasEntry(DateTime date) const
{	
	return news.find(date) != news.end();
}

bool NewsArchive::hasEntry(std::string title) const
{
	return news_journal.find(title) != news_journal.end();
}

std::string const & NewsArchive::getEntryTitle(DateTime  date) const
{
	std::map<DateTime, New>::const_iterator iterator = news.find(date);
	if (iterator == news.end()) 
	{
		throw std::logic_error(Messages::EntryDoesNotExist);
	}
		
	return iterator->second.m_title;
}

std::string const & NewsArchive::getEntryText(DateTime date) const
{
	std::map<DateTime, New>::const_iterator iterator= news.find(date);
	if (iterator == news.end())
	{
		throw std::logic_error(Messages::EntryDoesNotExist);
	}
		
	return iterator->second.m_text;
}

std::string const & NewsArchive::getEntryText(std::string title) const
{
	std::map<std::string, DateTime>::const_iterator iterator= news_journal.find(title);
	if (iterator == news_journal.end())
	{
		throw std::logic_error(Messages::EntryDoesNotExist);
	}
		
	return news.find(iterator->second)->second.m_text;
}

DateTime const & NewsArchive::getEntryDate(std::string title) const
{
	std::map<std::string, DateTime>::const_iterator iterator= news_journal.find(title);
	if (iterator == news_journal.end())
	{
		throw std::logic_error(Messages::EntryDoesNotExist);
	}
		
	return iterator->second;
}

void NewsArchive::forEachEntry(NewsArchive::EntryHandler _f) const
{
	for (auto n : news)
	{
		_f(n.first, n.second.m_title, n.second.m_text);
	}
}

void NewsArchive::addEntry(DateTime date,std::string title,std::string text)
{
	if (title.empty())
	{
		throw std::logic_error(Messages::EmptyEntryTitle);
	}
		
	if (text.empty())
	{
		throw std::logic_error(Messages::EmptyEntryText);
	}
		
	std::map<DateTime, New>::iterator iterator1 = news.find(date);

	std::map<std::string, DateTime>::iterator iterator2 = news_journal.find(title);

	if (iterator1 != news.end() || iterator2 != news_journal.end())
	{
		throw std::logic_error(Messages::DuplicatedEntry);
	}
	
	news.insert(std::make_pair(date, New(title,text)));

	news_journal.insert(std::make_pair(title,date));
}

void NewsArchive::modifyEntryTitle(DateTime date,std::string new_title)
{
	if (new_title.empty())
	{
		throw std::logic_error(Messages::EmptyEntryTitle);
	}
		
	std::map<DateTime, New>::iterator iterator1 = news.find(date);

	if (iterator1 == news.end())
	{
		throw std::logic_error(Messages::EntryDoesNotExist);
	}
		
	news_journal.erase(iterator1->second.m_title);
	
	iterator1->second.m_title = new_title;
	
	news_journal.insert(std::make_pair(new_title, date));
}

void NewsArchive::modifyEntryText(DateTime date, std::string new_text)
{
	if (new_text.empty())
	{
		throw std::logic_error(Messages::EmptyEntryText);
	}
	
	std::map<DateTime, New>::iterator iterator= news.find(date);
	if (iterator == news.end())
	{
		throw std::logic_error(Messages::EntryDoesNotExist);
	}
		
	iterator->second.m_text = new_text;
}

void NewsArchive::modifyEntryText(std::string title,std::string new_text)
{
	if (new_text.empty())
	{
		throw std::logic_error(Messages::EmptyEntryText);
	}
		
	std::map<std::string, DateTime>::iterator iterator1 = news_journal.find(title);
	if (iterator1 == news_journal.end())
	{
		throw std::logic_error(Messages::EntryDoesNotExist);
	}
		
	news.find(iterator1->second)->second.m_text = new_text;
}

void NewsArchive::removeEntry(DateTime  date)
{
	std::map<DateTime,New>::iterator iterator = news.find(date);
	
	if (iterator == news.end())
	{
		throw std::logic_error(Messages::EntryDoesNotExist);
	}
		
	news_journal.erase(news_journal.find(iterator->second.m_title));
	
	news.erase(iterator->first);
}

void NewsArchive::removeEntry(std::string  title)
{
	std::map<std::string, DateTime>::iterator iterator= news_journal.find(title);

	if (iterator == news_journal.end())
	{
		throw std::logic_error(Messages::EntryDoesNotExist);
	}
		
	news.erase(iterator->second);

	news_journal.erase(iterator);
}

std::vector<std::string> const NewsArchive::getEntryTitlesWithTextContains(std::string frag) const
{
	std::vector<std::string> resultVector;

	int fragment_counter;
	for (auto n : news)
	{
		fragment_counter = 0;
		for (int i = 0; i < n.second.m_text.size(); i++)
		{
			if (frag[fragment_counter] == n.second.m_text[i])
			{
				fragment_counter++;
			}
			else
			{
				fragment_counter = 0;
			}
			if (fragment_counter == frag.size())
			{
				break;
			}
		}

		if (fragment_counter == frag.size() || frag.empty())
		{
			resultVector.push_back(n.second.m_title);
		}
	}

	return resultVector;
}