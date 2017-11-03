// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _RECEIPT_HPP_
#define _RECEIPT_HPP_

/*****************************************************************************/

#include "messages.hpp"
#include <string>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <map>

/*****************************************************************************/

class Receipt
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/
	Receipt(
		std::string const & _ownerName,
		int _ownerID
	);

	Receipt(Receipt const &) = delete;

	Receipt(Receipt &&) = delete;

	Receipt & operator =(Receipt const &) = delete;

	Receipt & operator =(Receipt &&) = delete;

	/*-----------------------------------------------------------------*/
	
	std::string const & getPayerName() const;

	int getAccountNumber() const;

	bool hasServices() const;

	bool hasService(std::string const & _serviceName) const;

	int getServicesCount() const;

	void forEachService(std::function<void(std::string const &, double, double)> _f) const;

	double getDebtAmount(std::string const & _serviceName) const;

	double getPaidAmount(std::string const & _serviceName) const;

	void renameService(std::string const & _oldName, std::string const & _newName);

	void addService(std::string const & _serviceName);

	void removeService(std::string const & _serviceName);

	void trackDebt(std::string const & _serviceName, double _debt);

	void trackPay(std::string const & _serviceName, double _pay);

	double getTotalDebt() const;

	double getTotalPaid() const;

	std::vector<std::string> fetchOverpaid() const;

	std::vector<std::string> fetchUnderpaid() const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::string m_ownerName;
	
	int m_ownerID;

	std::unordered_map<std::string /*service_name */, double /* debt */> m_debtsLog;

	std::unordered_map<std::string /*service_name */, double /* payment */> m_paymentsLog;

/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline
std::string const & Receipt::getPayerName() const
{
	return m_ownerName;
}

/*****************************************************************************/

inline
int Receipt::getAccountNumber() const
{
	return m_ownerID;
}

/*****************************************************************************/

inline
bool Receipt::hasServices() const
{
	return !m_debtsLog.empty();
}

/*****************************************************************************/

inline
bool Receipt::hasService(std::string const & _serviceName) const
{
	return m_debtsLog.find(_serviceName) != m_debtsLog.end();
}

/*****************************************************************************/

inline
int Receipt::getServicesCount() const
{
	return m_debtsLog.size();
}

/*****************************************************************************/

inline
double Receipt::getDebtAmount(std::string const & _serviceName) const
{
	if (_serviceName.empty())
		throw std::logic_error(Messages::EmptyServiceName);

	if (m_debtsLog.find(_serviceName) == m_debtsLog.end())
		throw std::logic_error(Messages::ServiceDoesNotExist);

	return m_debtsLog.find(_serviceName)->second;
}

/*****************************************************************************/

inline
double Receipt::getPaidAmount(std::string const & _serviceName) const
{
	if (_serviceName.empty())
		throw std::logic_error(Messages::EmptyServiceName);

	if (m_paymentsLog.find(_serviceName) == m_paymentsLog.end())
		throw std::logic_error(Messages::ServiceDoesNotExist);

	return m_paymentsLog.find(_serviceName)->second;
}

/*****************************************************************************/


#endif // _RECEIPT_HPP_
