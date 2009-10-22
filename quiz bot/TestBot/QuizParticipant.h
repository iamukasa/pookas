#ifndef _QUIZ_PARTICIPANT_
#define _QUIZ_PARTICIPANT_

enum PlayerState{ QUIZPLAYER_CLICKED, QUIZPLAYER_REGISTERED };

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

private:
	int sessionID;
	PlayerState state; 
};

#endif