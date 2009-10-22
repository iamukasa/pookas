#ifndef _PARTICIPANT_MANAGER_H_
#define _PARTICIPANT_MANAGER_H_

#include <Vector>
#include <iostream>
#include "QuizParticipant.h" 

class ParticipantManager
{
public:
	ParticipantManager(void);
	~ParticipantManager(void);
	
	void Destroy(); 

	void setUser( int session, PlayerState state );
	void removeUser( int session ); 
	int userExists( int session ); 
	PlayerState getState( int session ); 
	void Print();
	
	void SetStartingPlayer( int session );
	int GetStartingPlayer();

private:
	std::vector <QuizParticipant*> quizUsers;
	int startingPlayerSID;
};

#endif