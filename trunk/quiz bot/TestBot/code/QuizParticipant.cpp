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

void QuizParticipant::setPos( int x, int y )
{
	pos.SetXY( x, y );
}

Vect2D QuizParticipant::getPos()
{
	return pos;
}