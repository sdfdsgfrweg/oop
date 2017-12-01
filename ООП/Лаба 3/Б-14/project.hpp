// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _PROJECT_HPP_
#define _PROJECT_HPP_

//---------------------------------------------------------------------------------

#include <string>
#include <set>
#include <map>
#include <functional>
#include <memory>

//---------------------------------------------------------------------------------

class Document;

//---------------------------------------------------------------------------------

class Project
{
public:

	//---------------------------------------------------------------------------------

	Project(std::string const & _projectName);

	~Project() = default;

	std::string const & getProjectName() const 
	{
		return m_name;
	}

	void addStandard(std::string const & _standard) 
	{
		m_standards.insert(_standard);
	}

	bool hasStandard(std::string const & _standard) const
	{
		return m_standards.find(_standard) != m_standards.end();
	}

	void addDocument(std::string const & _document, std::string const & _standard)
	{
		m_documents.insert(std::make_pair(_document, std::make_unique<Document>(_document, _standard)));
	}

	Document const & getDocument(std::string const & _document) const 
	{
		return *m_documents.find(_document)->second;
	}

	bool hasDocument(std::string const & _document) const 
	{
		return m_documents.find(_document) != m_documents.end();
	}

	void forEachStandard(std::function<void(std::string const & _s)> _f) const
	{
		for (auto const & s : m_standards)
			_f(s);
	}

	void forEachDocument(std::function<void(std::string const & _d, Document const & _p)> _f) const
	{
		for (auto & d : m_documents)
			_f(d.first, *d.second.get());
	}

	int getStandardsSize() const
	{
		return m_standards.size();
	}

	int getDocumentsSize() const {
		return m_documents.size();
	}

	//---------------------------------------------------------------------------------
private:

	//---------------------------------------------------------------------------------
	std::string m_name;

	std::set<std::string> m_standards;

	std::map<std::string, std::unique_ptr<Document>> m_documents;
	//---------------------------------------------------------------------------------
};



#endif // _PROJECT_HPP_
