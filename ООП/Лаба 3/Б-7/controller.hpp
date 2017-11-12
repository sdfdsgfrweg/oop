// (C) 2013-2016, Sergei Zaychenko, KNURE, Kharkiv, Ukraine

#ifndef _CONTROLLER_HPP_
#define _CONTROLLER_HPP_

/*****************************************************************************/

#include "datetime.hpp"
#include "meeting.hpp"
#include "participant.hpp"

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>


/*****************************************************************************/

class Controller
{

/*-----------------------------------------------------------------*/

public:

/*-----------------------------------------------------------------*/

	Controller ();

	~ Controller ();

	Controller ( const Controller & ) = delete;

	Controller & operator = ( const Controller & ) = delete;

/*-----------------------------------------------------------------*/

	void addParticipant (
			const std::string & _fullName
		,	const std::string & _email
	);

	const std::string & getParticipantEmail ( const std::string & _fullName ) const;

/*-----------------------------------------------------------------*/

	void addMeeting (
			int _meetingId
		,	const std::string & _name
		,	const DateTime & _startTime
	);

	const std::string & getMeetingName ( int _meetingId ) const;

	const DateTime & getMeetingStartTime ( int _meetingId ) const;

/*-----------------------------------------------------------------*/

	void addMeetingParticipant ( int _meetingId, const std::string & _participantName );

	void removeMeetingParticipant ( int _meetingId, const std::string & _participantName );

	void setMeetingModerator ( int _meetingId, const std::string & _participantName );

	std::string getMeetingModeratorName ( int _meetingId ) const;

	std::vector< std::string > getMeetingParticipants ( int _meetingId ) const;

	void validateMeceting ( int _meetingId ) const;

/*-----------------------------------------------------------------*/

	void addMeetingAgendaRow ( int _meetingId, const std::string & _agendaRow );

	std::vector< std::string > getMeetingAgenda ( int _meetingId ) const;

/*-----------------------------------------------------------------*/

	std::string getMostFrequentModeratorName () const;

	std::string getMeetingWithLongestAgenda () const;

	// NOTE: Key - participant, Value - meetings
	std::map< std::string, std::vector< std::string > > getOverlaps() const;

/*-----------------------------------------------------------------*/

private:

/*-----------------------------------------------------------------*/

	std::unordered_map<std::string, std::unique_ptr<Participant> > m_participants;

	std::map<int, std::unique_ptr<Meeting> > m_meetings;

/*-----------------------------------------------------------------*/ 
};


/*****************************************************************************/

#endif // _CONTROLLER_HPP_
