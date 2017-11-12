// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "datetime.hpp"
#include "date.hpp"

#include <vector>
#include <string>

#include <memory>
#include <unordered_map>

/*****************************************************************************/

class Organization;
class Payment;

class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	~Controller ();

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;

/*-----------------------------------------------------------------*/

	void addOrganization (
			const std::string & _name
		,	const std::string & _registrationNumber
		,	double _initialBalance
	);

	const std::string & getRegistrationNumber ( const std::string & _organizationName ) const;

	double getBalance ( const std::string & _organizationName ) const;

/*-----------------------------------------------------------------*/

	void addPayment (
			const std::string & _senderName
		,	const std::string & _recieverName
		,	const std::string & _paymentId
		,	const std::string & _purpose
		,	DateTime _time
		,	double _sum
	);

/*-----------------------------------------------------------------*/

	const std::string & getSenderName ( const std::string & _paymentId ) const;

	const std::string & getReceiverName ( const std::string & _paymentId ) const;

	const std::string & getPaymentPurpose ( const std::string & _paymentId ) const;

	DateTime getPaymentDateTime ( const std::string & _paymentId ) const;

	double getPaymentSum ( const std::string & _paymentId ) const;

/*-----------------------------------------------------------------*/

	// NOTE: First - organization name, second - balance
	std::vector< std::pair< std::string, double > > getFinalBalances () const;

	std::vector< std::string > getOrganizationsWithNegativeSaldo () const;

	std::string getIdOfBiggestPayment () const;

	Date getDateWithBiggestTotalPayments () const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::unordered_map<std::string, std::unique_ptr<Organization> > m_organizations;

	std::unordered_map<std::string, std::unique_ptr<Payment> > m_payments;

/*-----------------------------------------------------------------*/  

};

/*****************************************************************************/

#endif // _CONTROLLER_HPP_
