// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _USER_HPP_
#define _USER_HPP_

#include "ownershiprights.hpp"

#include <unordered_map>
#include <string>
#include <functional>

class Document;

class User
{
	std::string m_login;
	std::string m_fullName;
	std::unordered_map<Document const *, OwnershipRights> m_documents;

public:

	User(std::string const & _login,std::string const & _fullName);
	~User() = default;
	std::string const & getLogin() const;
	std::string const & getFullName() const;
	void addDocument(Document const & _doc, OwnershipRights _r);
	void changeDocumentRights(Document const & _doc, OwnershipRights _newR);
	bool hasDocumentRights(Document const & _doc) const;
	OwnershipRights getDocumentRights(Document const & _doc) const;
	void forEachDocument(std::function<void(Document const & _doc, OwnershipRights _r)> _f);
};

inline
std::string const & User::getLogin() const
{
	return m_login;
}

inline
std::string const & User::getFullName() const
{
	return m_fullName;
}

#endif // _USER_HPP_
