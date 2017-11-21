// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "messages.hpp"
#include "user.hpp"
#include "document.hpp"

/*****************************************************************************/

Controller::Controller() = default;

/*****************************************************************************/

Controller::~Controller() = default;

/*****************************************************************************/

void Controller::addUser(std::string const & _login, std::string const & _fullName)
{
	if (_login.empty())
		throw std::logic_error(Messages::UserLoginIsEmpty);

	if (_fullName.empty())
		throw std::logic_error(Messages::UserFullNameEmpty);

	if (m_users.find(_login) != m_users.end())
		throw std::logic_error(Messages::UserLoginAlreadyExists);
		
	m_users.insert(std::make_pair(_login,std::make_unique<User>(_login, _fullName)));
}

/*****************************************************************************/

std::string const & Controller::getUserFullName(std::string const & _login) const
{
	if (m_users.find(_login) == m_users.end())
		throw std::logic_error(Messages::UserLoginDoesNotExist);

	return m_users.find(_login)->second->getFullName();
}

/*****************************************************************************/

void Controller::addDocument(
	int _documentID,
	std::string const & _name,
	std::string const & _path,
	OwnershipRights _defaultRight
)
{
	if (m_documents.find(_documentID) != m_documents.end())
		throw std::logic_error(Messages::DocumentAlreadyExists);

	if (_name.empty())
		throw std::logic_error(Messages::DocumentNameIsEmpty);

	if (_path.empty())
		throw std::logic_error(Messages::DocumentPathIsEmpty);

	m_documents.insert(std::make_pair(_documentID, std::make_unique<Document>(_documentID, _name, _path, _defaultRight)));
}

/*****************************************************************************/

std::string const & Controller::getDocumentName(int _documentID) const
{
	if (m_documents.find(_documentID) == m_documents.end())
		throw std::logic_error(Messages::DocumentDoesNotExist);

	return m_documents.find(_documentID)->second->getName();
}

/*****************************************************************************/

std::string const & Controller::getDocumentPath(int _documentID) const
{
	if (m_documents.find(_documentID) == m_documents.end())
		throw std::logic_error(Messages::DocumentDoesNotExist);

	return m_documents.find(_documentID)->second->getPath();
}

/*****************************************************************************/

OwnershipRights Controller::getDocumentDefaultRights(int _documentID) const
{
	if (m_documents.find(_documentID) == m_documents.end())
		throw std::logic_error(Messages::DocumentDoesNotExist);

	return m_documents.find(_documentID)->second->getRights();
}

/*****************************************************************************/

void Controller::addDocumentRightsForUser(std::string const & _userLogin, int _documentID, OwnershipRights _rights)
{
	if (m_documents.find(_documentID) == m_documents.end())
		throw std::logic_error(Messages::DocumentDoesNotExist);

	if (m_users.find(_userLogin) == m_users.end())
		throw std::logic_error(Messages::UserLoginDoesNotExist);

	if (m_users.find(_userLogin)->second->hasDocumentRights(*m_documents.find(_documentID)->second.get()))
		throw std::logic_error(Messages::DocumentRightsAlreadyDefined);

	m_users.find(_userLogin)->second->addDocument(*m_documents.find(_documentID)->second.get(), _rights);
}

/*****************************************************************************/

void Controller::changeDocumentRightsForUser(std::string const & _userLogin, int _documentID, OwnershipRights _rights)
{
	if (m_documents.find(_documentID) == m_documents.end())
		throw std::logic_error(Messages::DocumentDoesNotExist);

	if (m_users.find(_userLogin) == m_users.end())
		throw std::logic_error(Messages::UserLoginDoesNotExist);

	if (!m_users.find(_userLogin)->second->hasDocumentRights(*m_documents.find(_documentID)->second.get()))
		throw std::logic_error(Messages::DocumentRightsUndefined);

	m_users.find(_userLogin)->second->changeDocumentRights(*m_documents.find(_documentID)->second.get(), _rights);
}

/*****************************************************************************/

void Controller::eraseDocumentRightsForUser(std::string const & _userLogin, int _documentID)
{
	if (m_documents.find(_documentID) == m_documents.end())
		throw std::logic_error(Messages::DocumentDoesNotExist);

	if (m_users.find(_userLogin) == m_users.end())
		throw std::logic_error(Messages::UserLoginDoesNotExist);

	if (!m_users.find(_userLogin)->second->hasDocumentRights(*m_documents.find(_documentID)->second.get()))
		throw std::logic_error(Messages::DocumentRightsUndefined);

	m_users.find(_userLogin)->second->changeDocumentRights(
		*m_documents.find(_documentID)->second.get(),
		m_documents.find(_documentID)->second->getRights());
}

/*****************************************************************************/

OwnershipRights Controller::getDocumentRightsForUser(std::string const & _userLogin, int _documentID) const
{
	if (m_documents.find(_documentID) == m_documents.end())
		throw std::logic_error(Messages::DocumentDoesNotExist);

	if (m_users.find(_userLogin) == m_users.end())
		throw std::logic_error(Messages::UserLoginDoesNotExist);

	OwnershipRights result;
	m_users.find(_userLogin)->second->forEachDocument(
		[&](Document const & _d, OwnershipRights _r)
	{
		if (_d.getID() == _documentID)
		{
			result = _r;
			return;
		}
	}
	);
	return result;
}

/*****************************************************************************/

Controller::AllRights Controller::getUserPermissionsReport() const
{
	AllRights permissions;

	for (auto const & u : m_users)
	{
		std::unordered_map<int, OwnershipRights> rights;
		for (auto const & d : m_documents)
		{
			if (u.second->hasDocumentRights(*d.second.get()))
				rights.insert(std::make_pair(d.second->getID(), u.second->getDocumentRights(*d.second.get())));
			else
				rights.insert(std::make_pair(d.second->getID(), d.second->getRights()));
		}
		permissions.insert(std::make_pair(u.first, rights));
	}
	return permissions;
}

/*****************************************************************************/

Controller::DocumentsInfo Controller::getDocumentsNotHavingPermittedUsers() const
{
	DocumentsInfo documents;

	for (auto const & d : m_documents)
	{
		bool hasAccess = false;
		for (auto const & u : m_users)
			if (u.second->hasDocumentRights(*d.second.get()))
				hasAccess = true;

		if (!hasAccess)
			documents.insert(std::make_pair(d.second->getID(), d.second->getName()));
	}

	return documents;
}

/*****************************************************************************/

std::unordered_set<std::string> Controller::getUsersNotHavingPermittedDocuments() const
{
	std::unordered_set<std::string> users;

	for (auto const & u : m_users) 
	{
		bool hasAccess = false;

		for (auto const & d : m_documents)
			if (u.second->hasDocumentRights(*d.second.get()))
				hasAccess = true;

		if (!hasAccess)
			users.insert(u.first);
	}

	return users;
}

/*****************************************************************************/

Controller::DocumentsInfo Controller::getDocumentsHavingMultipleWriteUsers() const
{
	DocumentsInfo documents;

	for (auto const & d : m_documents)
	{
		int userCounter = 0;
		for (auto const & u : m_users)
			if (u.second->getDocumentRights(*d.second.get()) == OwnershipRights::ReadAndWrite ||
				d.second->getRights() == OwnershipRights::ReadAndWrite)
				userCounter++;

		if (userCounter > 1)
			documents.insert(std::make_pair(d.second->getID(), d.second->getName()));
	}

	return documents;
}

/*****************************************************************************/