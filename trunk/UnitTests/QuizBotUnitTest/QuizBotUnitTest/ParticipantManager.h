#ifndef _PARTICIPANT_MANAGER_H_
#define _PARTICIPANT_MANAGER_H_

#include <Vector>
#include <iostream>
#include "QuizParticipant.h" 
#include "aw.h" 

class ParticipantManager
{
public:
	ParticipantManager(void);
	~ParticipantManager(void);
	
	void Destroy(); 

	void setUser( int session, PlayerState state );
	void setAllUsers ( PlayerState state ); 
	void removeUser( int session ); 
	void removeAllUsers(); 
	int userExists( int session ); 
	PlayerState getState( int session ); 
	void setState( int session, PlayerState state );
	void print();
	
	void setStartingPlayer( int session );
	int getStartingPlayer();
	
	void setPlayerPos( int session, int x, int y );
	Vect2D* getPlayerPos( int session );
	void broadcast( std::string message );
private:
	std::vector <QuizParticipant*> quizUsers;
	int startingPlayerSID;
};

#endif