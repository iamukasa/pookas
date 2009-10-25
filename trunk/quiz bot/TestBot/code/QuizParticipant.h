#ifndef _QUIZ_PARTICIPANT_
#define _QUIZ_PARTICIPANT_

#include <iostream>
#include "Vect3D.h" 
#include "aw.h"

enum PlayerState{ QUIZPLAYER_CLICKED, QUIZPLAYER_REGISTERED, QUIZPLAYER_STARTER, QUIZPLAYER_INVALID };

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
	
	void setName(std::string n);
	std::string getName();

	bool checkCollision( Vect3D objPos, int radius );
	void addScore();
	int getScore();

private:
	int sessionID;
	PlayerState state;
	int score; 
	std::string name; 
};

#endif