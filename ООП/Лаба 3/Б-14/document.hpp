// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _DOCUMENT_HPP_
#define _DOCUMENT_HPP_

//---------------------------------------------------------------------------------

#include <string>

//---------------------------------------------------------------------------------

class Document
{

public:

	//---------------------------------------------------------------------------------
	Document(std::string const & _Name,std::string const & _standard);

	~Document() = default;

	std::string const & getName() const {
		return m_name;
	}

	std::string const & getStandart() const
	{
		return m_standard;
	}

	//---------------------------------------------------------------------------------
private:

	//---------------------------------------------------------------------------------
	std::string m_name;

	std::string m_standard;
	//---------------------------------------------------------------------------------
};

#endif // _DOCUMENT_HPP_
