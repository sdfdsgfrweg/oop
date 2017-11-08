// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "wishlist.hpp"
#include <iostream>
#include <functional>

/*****************************************************************************/

Wishlist::Wishlist(std::string const & _ownerName)
	: m_ownerName(_ownerName)
{
	if (m_ownerName.empty())
		throw std::logic_error(Messages::OwnerNameEmpty);
}

/*****************************************************************************/

Wishlist::Wishlist(std::string const & _ownerName, std::initializer_list<Wish> _wishes)
	: m_ownerName(_ownerName)
{
	if (m_ownerName.empty())
		throw std::logic_error(Messages::OwnerNameEmpty);

	for (auto wish : _wishes)
	{
		if (wish.first.empty())
			throw std::logic_error(Messages::WishNameEmpty);

		if (wish.second < 0)
			throw std::logic_error(Messages::NegativePriority);
		
		if (m_wishesOrderedByName.find(wish.first) != m_wishesOrderedByName.end())
			throw std::logic_error(Messages::WishAlreadyExists);

		m_wishesOrderedByName.insert(std::make_pair(wish.first, std::move(wish)));
	}
}

/*****************************************************************************/

Wishlist::Wishlist(std::string const & _ownerName, std::vector<Wish> & _wishes)
	: m_ownerName(_ownerName)
{
	if (m_ownerName.empty())
		throw std::logic_error(Messages::OwnerNameEmpty);

	for (auto wish : _wishes)
	{
		m_wishesOrderedByName.insert(std::make_pair(wish.first, std::move(wish)));
		m_wishesOrderedByPriority.push_back(std::make_pair(wish.second, wish.first));
	}
}

/*****************************************************************************/

Wishlist::Wishlist(Wishlist && _wish)
{
	std::swap(m_ownerName, _wish.m_ownerName);
	m_wishesOrderedByName = std::move(_wish.m_wishesOrderedByName);
	m_wishesOrderedByPriority = std::move(_wish.m_wishesOrderedByPriority);
}

/*****************************************************************************/

void Wishlist::operator+=(const Wish & _wish)
{
	if (_wish.first.empty())
		throw std::logic_error(Messages::WishNameEmpty);

	if (_wish.second < 0)
		throw std::logic_error(Messages::NegativePriority);

	if (m_wishesOrderedByName.find(_wish.first) != m_wishesOrderedByName.end())
		throw std::logic_error(Messages::WishAlreadyExists);

	m_wishesOrderedByName.insert(std::make_pair(_wish.first, _wish));
	m_wishesOrderedByPriority.push_back(std::make_pair(_wish.second, _wish.first));
}

/*****************************************************************************/

std::vector<std::string> Wishlist::getMostPrioritizedWishes(int _wishesNumber) const
{
	if (_wishesNumber < 1)
		throw std::logic_error(Messages::NonPositiveAmount);
	
	std::vector<std::string> mostPrioritizedWishes;
	std::set<int,std::greater<int>> onlyPriorities;

	for (int i = 0; i < m_wishesOrderedByPriority.size(); i++)
		onlyPriorities.insert(m_wishesOrderedByPriority[i].first);

	int count = 0;
	for (auto it = onlyPriorities.begin(); it != onlyPriorities.end(); ++it)
	{
		for (int j = 0; j < m_wishesOrderedByPriority.size(); j++)
		{
			if (*it == m_wishesOrderedByPriority[j].first)
			{
				mostPrioritizedWishes.push_back(m_wishesOrderedByPriority[j].second);
				count++;
			}
			if (count == _wishesNumber)
				return mostPrioritizedWishes;
		}
	}
	return mostPrioritizedWishes;
}

/*****************************************************************************/

std::vector<std::string> Wishlist::getLeastPrioritizedWishes(int _wishesNumber) const
{
	if (_wishesNumber < 1)
		throw std::logic_error(Messages::NonPositiveAmount);

	std::vector<std::string> leastPrioritizedWishes;

	std::set<int> onlyPriorities;

	for (int i = 0; i < m_wishesOrderedByPriority.size(); i++)
		onlyPriorities.insert(m_wishesOrderedByPriority[i].first);

	int count = 0;
	for (auto it = onlyPriorities.begin(); it != onlyPriorities.end(); ++it)
	{
		if (count == _wishesNumber)
			break;

		for (int j = 0; j < m_wishesOrderedByPriority.size(); j++)
		{
			if (*it == m_wishesOrderedByPriority[j].first)
			{
				leastPrioritizedWishes.push_back(m_wishesOrderedByPriority[j].second);
				count++;
			}
			if (count == _wishesNumber)
				break;
		}
	}

	return leastPrioritizedWishes;
}

/*****************************************************************************/

std::set<std::string> Wishlist::getSimilarWishes(const Wishlist & _wish) const
{
	std::set<std::string> similarWishes;

	for (auto lhs : m_wishesOrderedByName)
		for (auto rhs : _wish.m_wishesOrderedByName)
			if (lhs.first == rhs.first)
				similarWishes.insert(lhs.first);

	return similarWishes;
}

/*****************************************************************************/

void Wishlist::dropWish(std::string const & _wishName)
{
	if (_wishName.empty())
		throw std::logic_error(Messages::WishNameEmpty);

	if (m_wishesOrderedByName.find(_wishName) == m_wishesOrderedByName.end())
		throw std::logic_error(Messages::WishDoesNotExist);
	
	for (auto it = m_wishesOrderedByPriority.begin(); it != m_wishesOrderedByPriority.end(); it++)
		if ((*it).second == _wishName)
		{
			m_wishesOrderedByPriority.erase(it);
			break;
		}
	m_wishesOrderedByName.erase(_wishName);
}

/*****************************************************************************/

void Wishlist::dropWishesWithPriorityLessThan(int _wishPriority)
{
	for (int i = 0; i < m_wishesOrderedByPriority.size(); i++)
	{
		if (m_wishesOrderedByPriority[i].first < _wishPriority)
		{
			m_wishesOrderedByName.erase(m_wishesOrderedByPriority[i].second);
			m_wishesOrderedByPriority.erase(m_wishesOrderedByPriority.begin() + i);
			i = 0;
		}

		if (m_wishesOrderedByPriority.size() == 1 && m_wishesOrderedByPriority[i].first < _wishPriority)
		{
			m_wishesOrderedByName.erase(m_wishesOrderedByPriority[i].second);
			m_wishesOrderedByPriority.erase(m_wishesOrderedByPriority.begin());
			return;
		}
	}
}

/*****************************************************************************/

std::vector<std::string> Wishlist::getWishesWithPriority(int _wishesPriority) const
{
	if (_wishesPriority < 0)
		throw std::logic_error(Messages::NegativePriority);

	std::vector<std::string> wishes;

	for (auto wish : m_wishesOrderedByPriority)
		if (wish.first == _wishesPriority)
			wishes.push_back(wish.second);

	return wishes;
}

/*****************************************************************************/