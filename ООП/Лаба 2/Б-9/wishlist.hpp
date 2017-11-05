// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _WISHLIST_HPP_
#define _WISHLIST_HPP_

/*****************************************************************************/

#include "messages.hpp"
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>

/*****************************************************************************/

	typedef
	std::pair< std::string, int >
	Wish;

/*****************************************************************************/


class Wishlist
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/
	
	Wishlist(std::string const & _ownerName);

	Wishlist(
		std::string const & _ownerName,
		std::initializer_list<Wish> _wishes	
	);

	Wishlist(
		std::string const & _ownerName,
		std::vector<Wish> & _wishes
	);

	Wishlist(Wishlist && _wish);

	std::string const & getOwner() const;

	void correctOwner(std::string const & _correctOwnerName);

	void addWish(std::string const & _wishName, int _wishPriority);

	void addWish(Wish const & _wish);

	bool hasWish(std::string const & _wishName) const;

	int getWishPriority(std::string const & _wishName) const;

	int getWishesCount() const;

	void updateWishPriority(std::string const & _wishName, int _newWishPriority);

	void clean();

	void operator += (const Wish & _wish);

	Wish & operator[](int _index);

	std::vector<std::string> getWishesWithPriority(int _wishesPriority) const;

	std::vector<std::string> getMostPrioritizedWishes(int _wishesNumber) const;

	std::vector<std::string> getLeastPrioritizedWishes(int _wishesNumber) const;

	std::set<std::string> getSimilarWishes(const Wishlist & _wish) const;

	void dropWish(std::string const & _wishName);

	void dropWishesWithPriorityLessThan(int _wishPriority);


/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string m_ownerName;

	std::unordered_map<std::string, Wish> m_wishesOrderedByName;

	std::vector<std::pair<int, std::string>> m_wishesOrderedByPriority;

/*-----------------------------------------------------------------*/

};


/*****************************************************************************/

inline
std::string const & Wishlist::getOwner() const
{
	return m_ownerName;
}

inline
void Wishlist::correctOwner(std::string const & _correctOwnerName)
{
	if (_correctOwnerName.empty())
		throw std::logic_error(Messages::OwnerNameEmpty);

	m_ownerName = _correctOwnerName;
}

inline
void Wishlist::addWish(std::string const & _wishName, int _wishPriority)
{
	if (_wishName.empty())
		throw std::logic_error(Messages::WishNameEmpty);

	if (m_wishesOrderedByName.find(_wishName) != m_wishesOrderedByName.end())
		throw std::logic_error(Messages::WishAlreadyExists);

	if (_wishPriority < 0)
		throw std::logic_error(Messages::NegativePriority);

	m_wishesOrderedByName.insert(std::make_pair(_wishName, std::make_pair(_wishName, _wishPriority)));
	m_wishesOrderedByPriority.push_back(std::make_pair(_wishPriority,_wishName));
}

inline
void Wishlist::addWish(Wish const & _wish)
{
	if (_wish.first.empty())
		throw std::logic_error(Messages::WishNameEmpty);

	if (m_wishesOrderedByName.find(_wish.first) != m_wishesOrderedByName.end())
		throw std::logic_error(Messages::WishAlreadyExists);

	if (_wish.second < 0)
		throw std::logic_error(Messages::NegativePriority);

	m_wishesOrderedByName.insert(std::make_pair(_wish.first, Wish(_wish.first, _wish.second)));
	m_wishesOrderedByPriority.push_back(std::make_pair(_wish.second,_wish.first));
}

inline
bool Wishlist::hasWish(std::string const & _wishName) const
{
	if (_wishName.empty())
		throw std::logic_error(Messages::WishNameEmpty);
	
	return m_wishesOrderedByName.find(_wishName) != m_wishesOrderedByName.end();
}

inline
int Wishlist::getWishPriority(std::string const & _wishName) const
{
	if (_wishName.empty())
		throw std::logic_error(Messages::WishNameEmpty);

	if (m_wishesOrderedByName.find(_wishName) == m_wishesOrderedByName.end())
		throw std::logic_error(Messages::WishDoesNotExist);

	return m_wishesOrderedByName.find(_wishName)->second.second;
}

inline
int Wishlist::getWishesCount() const
{
	return m_wishesOrderedByName.size();
}

inline
void Wishlist::updateWishPriority(std::string const & _wishName, int _newWishPriority)
{
	if (_wishName.empty())
		throw std::logic_error(Messages::WishNameEmpty);

	if (m_wishesOrderedByName.find(_wishName) == m_wishesOrderedByName.end())
		throw std::logic_error(Messages::WishDoesNotExist);

	if (_newWishPriority < 0)
		throw std::logic_error(Messages::NegativePriority);

	m_wishesOrderedByName.find(_wishName)->second.second = _newWishPriority;
	for (int i = 0; i < m_wishesOrderedByPriority.size(); i++)
		if (m_wishesOrderedByPriority[i].second == _wishName)
		{
			m_wishesOrderedByPriority[i].first = _newWishPriority;
			break;
		}
}

inline
void Wishlist::clean()
{
	m_wishesOrderedByName.clear();
	m_wishesOrderedByPriority.clear();
}

inline
Wish & Wishlist::operator[](int _index)
{
	if (_index < 0 || _index >= m_wishesOrderedByName.size())
		throw std::out_of_range("");

	int counter = 0;
	auto it = m_wishesOrderedByName.begin();
	for (it; counter != _index; it++, counter++);

	return it->second;
}

/*****************************************************************************/


#endif // _WISHLIST_HPP_
