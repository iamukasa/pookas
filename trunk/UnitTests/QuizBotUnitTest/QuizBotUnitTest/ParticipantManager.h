/** \class ParticipantManager
Manages quiz players.
*/

#ifndef _PARTICIPANT_MANAGER_H_
#define _PARTICIPANT_MANAGER_H_

#include <Vector>
#include <iostream>
#include <string>
#include "QuizParticipant.h" 
#include "aw.h" 

class ParticipantManager
{
public:
	ParticipantManager(void);
	~ParticipantManager(void);
	
	void destroy(); 

	void setUser( int session, PlayerState state );
	void setAllUsers ( PlayerState state ); 

	void removeUser( int session ); 
	void removeAllUsers(); 
	void removeAllWithState( PlayerState state ); 

	int userExists( int session ); 
	PlayerState getState( int session ); 
	void setState( int session, PlayerState state );
	void print();
	
	void setStartingPlayer( int session );
	int getStartingPlayer();

	void setPlayerName( int session, std::string name );
	std::string getPlayerName( int session );
	
	void broadcast( std::string message, int r, int g, int b, int bold, int italic );
	static void whisper( int session, std::string message, int r, int g, int b, int bold, int italic );
	void checkAnswers( Vect3D objPos, int radius );
	void broadcastTopScores();
	
	void reset();

	std::vector <QuizParticipant*> quizUsers;
	int startingPlayerSID;
	int topScore;
};

#endif