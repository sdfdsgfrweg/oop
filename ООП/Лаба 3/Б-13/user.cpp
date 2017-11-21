// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "user.hpp"
#include "messages.hpp"
#include "document.hpp"

/*****************************************************************************/

User::User(
	std::string const & _login,
	std::string const & _fullName
)
	: m_login(_login)
	, m_fullName(_fullName)
{}

/*****************************************************************************/

void User::addDocument(Document const & _doc, OwnershipRights _r)
{
	m_documents.insert(std::make_pair(&_doc, _r));
}

/*****************************************************************************/

void User::changeDocumentRights(Document const & _doc, OwnershipRights _newR)
{
	for (auto & d : m_documents)
		if (d.first->getID() == _doc.getID())
		{
			d.second = _newR;
			break;
		}
}

/*****************************************************************************/

bool User::hasDocumentRights(Document const & _doc) const
{
	for (auto const & d : m_documents)
		if (d.first->getID() == _doc.getID())
			return d.second != OwnershipRights::NoAccess;
	return false;
}

/*****************************************************************************/

OwnershipRights User::getDocumentRights(Document const & _doc) const
{
	for (auto const & d : m_documents)
		if (d.first->getID() == _doc.getID())
			return d.second;
}

/*****************************************************************************/

void User::forEachDocument(std::function<void(Document const&_doc, OwnershipRights _r)> _f)
{
	for (auto const & d : m_documents)
		_f(*d.first, d.second);
}

/*****************************************************************************/
