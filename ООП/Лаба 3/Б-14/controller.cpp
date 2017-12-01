// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "controller.hpp"
#include "project.hpp"
#include "document.hpp"
#include "messages.hpp"
#include <iostream>

//---------------------------------------------------------------------------------

Controller::Controller() = default;

//---------------------------------------------------------------------------------

Controller::~Controller() = default;

//---------------------------------------------------------------------------------

void Controller::addProject(std::string const & _projectName)
{
	if (_projectName.empty()) throw std::logic_error(Messages::ProjectNameIsEmpty);
	if (hasProject(_projectName)) throw std::logic_error(Messages::ProjectAlreadyExists);
		
	m_projects.insert(std::make_pair(_projectName, std::make_unique<Project>(_projectName)));
}

//---------------------------------------------------------------------------------

int Controller::getProjectsCount() const
{
	return m_projects.size();
}

//---------------------------------------------------------------------------------

bool Controller::hasProject(std::string const & _projectName) const
{
	return m_projects.find(_projectName) != m_projects.end();
}

//---------------------------------------------------------------------------------

int Controller::getProjectDocumentsCount(std::string const & _projectName) const
{
	if (!hasProject(_projectName)) throw std::logic_error(Messages::ProjectDoesNotExist);
		
	return m_projects.find(_projectName)->second->getDocumentsSize();
}

//---------------------------------------------------------------------------------

bool Controller::hasProjectDocument(std::string const & _projectName,std::string const & _documentName) const
{
	if (!hasProject(_projectName)) throw std::logic_error(Messages::ProjectDoesNotExist);
		
	return m_projects.find(_projectName)->second->hasDocument(_documentName);
}

//---------------------------------------------------------------------------------

std::string const & Controller::getProjectDocumentStandard(std::string const & _projectName,std::string const & _documentName) const
{
	if (!hasProject(_projectName)) throw std::logic_error(Messages::ProjectDoesNotExist);
		
	return m_projects.find(_projectName)->second->getDocument(_documentName).getStandart();
}

//---------------------------------------------------------------------------------

void Controller::addDocumentForProject(std::string const & _projectName,std::string const & _documentName,std::string const & _standardName)
{
	if (!hasProject(_projectName)) throw std::logic_error(Messages::ProjectDoesNotExist);
	if (_documentName.empty()) throw std::logic_error(Messages::DocumentNameIsEmpty);
	if (m_projects.find(_projectName)->second->hasDocument(_documentName)) throw std::logic_error(Messages::DocumentAlreadyExistsInProject);
		
	m_projects.find(_projectName)->second->addDocument(_documentName, _standardName);
}

//---------------------------------------------------------------------------------

void Controller::addStandardForProject(std::string const & _projectName,std::string const & _standardName)
{
	if (!hasProject(_projectName)) throw std::logic_error(Messages::ProjectDoesNotExist);
	if (_standardName.empty())throw std::logic_error(Messages::StandardNameIsEmpty);
	if (m_projects.find(_projectName)->second->hasStandard(_standardName)) throw std::logic_error(Messages::StandardAlreadyExistsInProject);
		
	m_projects.find(_projectName)->second->addStandard(_standardName);
}

//---------------------------------------------------------------------------------

int Controller::getProjectStandardsCount(std::string const & _projectName) const
{
	if (!hasProject(_projectName)) throw std::logic_error(Messages::ProjectDoesNotExist);
		
	return m_projects.find(_projectName)->second->getStandardsSize();
}

//---------------------------------------------------------------------------------

bool Controller::hasProjectStandard(std::string const & _projectName,std::string const & _standardName) const
{
	if (!hasProject(_projectName)) throw std::logic_error(Messages::ProjectDoesNotExist);
		
	return m_projects.find(_projectName)->second->hasStandard(_standardName);
}

//---------------------------------------------------------------------------------

Controller::StandardNames Controller::getProjectStandardsUsed() const
{
	StandardNames r;
	m_projects.begin()->second->forEachStandard(
		[&](std::string const & _s)
	{
		r.insert(_s);
	});
		
	auto iterator = ++m_projects.begin();
	for (iterator; iterator != m_projects.end(); ++iterator)
		iterator->second->forEachStandard(
			[&](std::string const & _s)
		{
			if (r.find(_s) == r.end())
				r.erase(_s);
		});

	return r;
}

//---------------------------------------------------------------------------------

Controller::ProjectNames Controller::getProjectsWithAllNeededStandardDocuments() const
{
	ProjectNames r;
	bool isNormal;

	for (auto const & p : m_projects)
	{
		isNormal = true;
		
		p.second->forEachDocument(
			[&](std::string const & _s, Document const & _d)
		{
			if (p.second->getStandardsSize() != 0 && !p.second->hasStandard(_d.getStandart()))
				isNormal = false;
		});
			
		if (isNormal) r.insert(p.first);
	};

	return r;
}

//---------------------------------------------------------------------------------

Controller::ProjectNames Controller::getProjectsNotHavingStandardDocument(std::string const & _standard) const
{
	ProjectNames r;
	for (auto const & p : m_projects)
		if (p.second->hasStandard(_standard))
			p.second->forEachDocument(
				[&](std::string const & _s, Document const & _d)
			{
				if (_d.getStandart().empty())
				{
					r.insert(p.first);
					return;
				}
			});
		else
			r.insert(p.first);

	return r;
}

//---------------------------------------------------------------------------------

std::string Controller::getMostPopularStandard() const
{
	std::map<int, std::string, std::greater<int>> standards;
	bool isBreaked;

	for (auto const & p : m_projects)
		p.second->forEachStandard(
			[&](std::string const & _s)
		{
			standards.insert(std::make_pair(0, _s));
		});

	for (auto const & p : m_projects)
		p.second->forEachDocument(
			[&](std::string const & _s, Document const & _d)
		{
			isBreaked = false;
			int curr = 0;
			auto c = standards;
			for (auto s : c)
			{
				if (s.second == _d.getStandart())
				{
					curr = s.first;
					standards.erase(curr);
					standards.insert(std::make_pair(curr++, s.second));
					isBreaked = true;
					break;
				}
			}
			if (isBreaked) return;
		});

	return standards.begin()->second;
}

//---------------------------------------------------------------------------------