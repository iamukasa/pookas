#ifndef _QUIZ_PARTICIPANT_
#define _QUIZ_PARTICIPANT_

#include "Vect2D.h" 

enum PlayerState{ QUIZPLAYER_CLICKED, QUIZPLAYER_REGISTERED, QUIZPLAYER_START, QUIZPLAYER_INVALID };

class QuizParticipant
{
public:
	QuizParticipant(void);
	QuizParticipant( int session );
	~QuizParticipant(void);

	void setState( PlayerState state ); 
	PlayerState getState(); 
	
	void setSessionID( int session );
	int getSessionID();

	void setPos( int x, int y );
	Vect2D getPos();

private:
	int sessionID;
	PlayerState state; 
	Vect2D pos;
};

#endif