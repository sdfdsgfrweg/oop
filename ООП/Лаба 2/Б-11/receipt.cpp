// (C) 2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#include "receipt.hpp"

/*****************************************************************************/

void Receipt::forEachService(std::function<void(std::string const&, double, double)> _f) const
{
	std::map < std::string, std::pair<double, double> > _union;
	for (auto debt : m_debtsLog)
		_union.insert(std::make_pair(debt.first, std::make_pair(debt.second, m_paymentsLog.find(debt.first)->second)));

	for (auto unit : _union)
		_f(unit.first, unit.second.first, unit.second.second);
}

/*****************************************************************************/

void Receipt::addService(std::string const & _serviceName)
{
	if (_serviceName.empty())
		throw std::logic_error(Messages::EmptyServiceName);

	if (m_debtsLog.find(_serviceName) != m_debtsLog.end())
		throw std::logic_error(Messages::DuplicatedService);

	m_debtsLog.insert(std::make_pair(_serviceName, 0.0));
	m_paymentsLog.insert(std::make_pair(_serviceName, 0.0));
}

/*****************************************************************************/

void Receipt::removeService(std::string const & _serviceName)
{
	if (_serviceName.empty())
		throw std::logic_error(Messages::EmptyServiceName);

	if (m_debtsLog.find(_serviceName) == m_debtsLog.end())
		throw std::logic_error(Messages::ServiceDoesNotExist);

	m_debtsLog.erase(_serviceName);
	m_paymentsLog.erase(_serviceName);
}

/*****************************************************************************/

void Receipt::trackDebt(std::string const & _serviceName, double _debt)
{
	if (_serviceName.empty())
		throw std::logic_error(Messages::EmptyServiceName);

	if (m_debtsLog.find(_serviceName) == m_debtsLog.end())
		throw std::logic_error(Messages::ServiceDoesNotExist);

	m_debtsLog.find(_serviceName)->second += _debt;
}

/*****************************************************************************/

void Receipt::renameService(std::string const & _oldName, std::string const & _newName)
{
	if (_oldName.empty() || _newName.empty())
		throw std::logic_error(Messages::EmptyServiceName);
	
	if (m_debtsLog.find(_oldName) == m_debtsLog.end())
		throw std::logic_error(Messages::ServiceDoesNotExist);

	if (m_debtsLog.find(_newName) != m_debtsLog.end())
		throw std::logic_error(Messages::DuplicatedService);

	m_debtsLog.insert(std::make_pair(_newName, m_debtsLog.find(_oldName)->second));
	m_debtsLog.erase(_oldName);

	m_paymentsLog.insert(std::make_pair(_newName, m_paymentsLog.find(_oldName)->second));
	m_paymentsLog.erase(_oldName);

}

/*****************************************************************************/

void Receipt::trackPay(std::string const & _serviceName, double _pay)
{
	if (_serviceName.empty())
		throw std::logic_error(Messages::EmptyServiceName);

	if (m_paymentsLog.find(_serviceName) == m_paymentsLog.end())
		throw std::logic_error(Messages::ServiceDoesNotExist);

	if (_pay < 0)
		throw std::logic_error(Messages::InvalidAmountValue);

	m_paymentsLog.find(_serviceName)->second += _pay;
}

/*****************************************************************************/

double Receipt::getTotalDebt() const
{
	double total = 0;
	for (auto debt : m_debtsLog) total += debt.second;
	return total;
}

/*****************************************************************************/

double Receipt::getTotalPaid() const
{
	double total = 0;
	for (auto pay : m_paymentsLog) total += pay.second;
	return total;
}

/*****************************************************************************/

std::vector<std::string> Receipt::fetchOverpaid() const
{
	std::vector<std::string> overpaidServices;
	
	for (auto debt : m_debtsLog) if (debt.second < 0) 
		overpaidServices.push_back(debt.first);

	std::sort(overpaidServices.begin(), overpaidServices.end());
	
	return overpaidServices;
}

/*****************************************************************************/

std::vector<std::string> Receipt::fetchUnderpaid() const
{
	std::vector<std::string> underpaidServices;

	for (auto debt : m_debtsLog) if (debt.second > 0) 
		underpaidServices.push_back(debt.first);

	std::sort(underpaidServices.begin(), underpaidServices.end());

	return underpaidServices;
}

/*****************************************************************************/

Receipt::Receipt(
	std::string const & _ownerName,
	int _ownerID
)
	: m_ownerName(_ownerName)
	, m_ownerID(_ownerID)
{
	if (m_ownerName.empty())
		throw std::logic_error(Messages::EmptyPayerName);

	if (m_ownerID < 1)
		throw std::logic_error(Messages::InvalidAccountNumber);
}

/*****************************************************************************/