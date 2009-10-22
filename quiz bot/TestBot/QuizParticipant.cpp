#include "QuizParticipant.h"

QuizParticipant::QuizParticipant(void)
{
}

QuizParticipant::QuizParticipant( int session )
{
	sessionID = session;
	state = QUIZPLAYER_CLICKED;
}

QuizParticipant::~QuizParticipant(void)
{
}

void QuizParticipant::setState( PlayerState s )
{
	state = s; 
}

PlayerState QuizParticipant::getState()
{
	return state;
}

void QuizParticipant::setSessionID( int session )
{
	sessionID = session;
}

int QuizParticipant::getSessionID()
{
	return sessionID;
}