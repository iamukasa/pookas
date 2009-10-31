#include "ParticipantManager.h"

ParticipantManager::ParticipantManager(void)
{
	int topScore = 0;
	startingPlayerSID = -1;
}

ParticipantManager::~ParticipantManager(void)
{
}

/** 
\fn void ParticipantManager::destroy()
\brief Called when program shutdown
*/
void ParticipantManager::destroy()
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		//delete
		delete quizUsers.at(i); 
	}

	quizUsers.clear();
}

/** 
\fn void ParticipantManager::setUser( int session, PlayerState state )
\brief Adds a user to the quiz. 
\param session Session ID of the player to be added
\param state State to set the player to
*/
void ParticipantManager::setUser( int session, PlayerState state )
{
	int userIndex = userExists(session);
	if ( userIndex != -1  ) 
	{
		//std::cout << "Setting user " << session << " state = " << state; 
		//set the session only
		quizUsers.at(userIndex)->setState(state);
	}
	
	else
	{
		QuizParticipant *p = new QuizParticipant(session);
		p->setState( state);
		std::cout << "Session ID : " << p->getSessionID() << std::endl;
		quizUsers.push_back(p);		
		//std::cout << "Added user " << session << " Num = " << quizUsers.size(); 
	}
}

/** 
\fn void ParticipantManager::setAllUsers ( PlayerState state )
\brief Sets a state for all users.
\param state State to set the players to
*/
void ParticipantManager::setAllUsers ( PlayerState state )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		quizUsers.at(i)->setState(state);

	}

}

/** 
\fn void ParticipantManager::removeUser( int session )
\brief Removes a user of a particular session ID.
\param session Session ID of the player
*/
void ParticipantManager::removeUser( int session )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getSessionID() == session )
		{
			quizUsers.erase(quizUsers.begin()+i, quizUsers.begin()+i+1 );
		}
	}
	std::cout << "Removing \n"; 
}

/** 
\fn void ParticipantManager::removeAllUsers()
\brief Clears the user list
*/
void ParticipantManager::removeAllUsers()
{
	quizUsers.clear();
	std::cout << "After clear\n";
}

/** 
\fn void ParticipantManager::removeAllWithState( PlayerState state )
\brief Removes all users with a particular state
\param state The state of the players to remove
*/
void ParticipantManager::removeAllWithState( PlayerState state )
{
	std::vector <int> toRemove;
	int numRemoved = 0;
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getState() == state )
		{			
			toRemove.push_back(i-numRemoved);
			numRemoved += 1;
		}
	}

	for ( unsigned int j = 0; j < toRemove.size(); j++ )
	{
		int removing = toRemove.at(j);
		quizUsers.erase(quizUsers.begin()+removing, quizUsers.begin()+removing+1 );
	}
}

/** 
\fn int ParticipantManager::userExists( int session )
\brief Check if a player is in the user list
\param session Session ID of the player.
\return The index of the player in the user list. If the player is not in the list, returns -1. 
*/
int ParticipantManager::userExists( int session )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		//std::cout << "Searching user" << session << " i= " << quizUsers.at(i)->getSessionID() << std::endl; 
		if ( quizUsers.at(i)->getSessionID() == session )
			return i;
	}

	return -1;
}

/** 
\fn PlayerState ParticipantManager::getState( int session )
\brief Gets the state of a player
\param session Session ID of the player
\return The state of the player
*/
PlayerState ParticipantManager::getState( int session )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getSessionID() == session )
			return quizUsers.at(i)->getState();
	}

	return QUIZPLAYER_INVALID;
}

/** 
\fn void ParticipantManager::setState( int session, PlayerState state )
\brief Sets the state of a player
\param session Session ID of the player
\param state The state to set the player to
*/
void ParticipantManager::setState( int session, PlayerState state )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getSessionID() == session )
			quizUsers.at(i)->setState( state ); 
	}
}

/** 
\fn void ParticipantManager::print()
\brief Prints out the players in the user list. 

Debugging purposes.
*/
void ParticipantManager::print()
{
	std::cout << "=======================" << std::endl;
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		std::cout << quizUsers.at(i)->getSessionID() << " " << quizUsers.at(i)->getState() << std::endl; 
	}
	std::cout << "=======================" << std::endl;

}

/** 
\fn void ParticipantManager::setStartingPlayer( int session )
\brief Sets the first player who started the quiz. 
\param session Session ID of the player
*/
void ParticipantManager::setStartingPlayer( int session )
{
	startingPlayerSID = session; 
}

/** 
\fn int ParticipantManager::getStartingPlayer()
\brief Gets the first player who started the quiz. 
\return Session ID of the player
*/
int ParticipantManager::getStartingPlayer()
{
	return startingPlayerSID;
}

/** 
\fn void ParticipantManager::broadcast( std::string message, int r, int g, int b, int bold, int italic )
\brief Broadcasts an ActiveWorlds console message to all players in the user list
\param message Message to broadcast
\param r Defines colour of the message
\param g Defines colour of the message
\param b Defines colour of the message
\param bold Makes the font bold
\param italic Makes the font italic
*/
void ParticipantManager::broadcast( std::string message, int r, int g, int b, int bold, int italic )
{
	int rc;
	std::string msg = "[QuizBot]:\t";
	msg += message;

	aw_int_set (AW_CONSOLE_RED, r);
	aw_int_set (AW_CONSOLE_GREEN, g);
	aw_int_set (AW_CONSOLE_BLUE, b);
	aw_bool_set (AW_CONSOLE_BOLD, bold);
	aw_bool_set (AW_CONSOLE_ITALICS, italic);

	aw_string_set (AW_CONSOLE_MESSAGE, msg.c_str());

	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( rc = aw_console_message ( quizUsers.at(i)->getSessionID()) )
		{
			std::cout << "Console message failed (reason "<< rc << ")\n";

		}
	}
}

/** 
\fn void ParticipantManager::whisper( int session, std::string message, int r, int g, int b, int bold, int italic )
\brief Whispers a message to a player
\param session Session ID of the player to whisper to
\param message Message to broadcast
\param r Defines colour of the message
\param g Defines colour of the message
\param b Defines colour of the message
\param bold Makes the font bold
\param italic Makes the font italic
*/
void ParticipantManager::whisper( int session, std::string message, int r, int g, int b, int bold, int italic )
{
	int rc;
	std::string msg = "[QuizBot]:\t";
	msg += message;

	aw_int_set (AW_CONSOLE_RED, r);
	aw_int_set (AW_CONSOLE_GREEN, g);
	aw_int_set (AW_CONSOLE_BLUE, b);
	aw_bool_set (AW_CONSOLE_BOLD, bold);
	aw_bool_set (AW_CONSOLE_ITALICS, italic);

	aw_string_set (AW_CONSOLE_MESSAGE, msg.c_str());

	
	if ( rc = aw_console_message ( session ) )
	{
		std::cout << "Console message failed (reason "<< rc << ")\n";

	}
}

/** 
\fn void ParticipantManager::checkAnswers( Vect3D objPos, int radius )
\brief Checks which players answered correctly
\param objPos Position of the tile with the correct answer
\param radius Sphere collision boundary. If the player is within this radius of the tile position, detect as correct.

Checks which players answered correctly and tells the player whether they are right or wrong. 
Increments their score accordingly.
*/
void ParticipantManager::checkAnswers( Vect3D objPos, int radius )
{
	std::string scoremsg;
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->checkCollision( objPos, radius ) )
		{
			quizUsers.at(i)->addScore(); 

			if ( quizUsers.at(i)->getScore() > topScore )
			{
				topScore = quizUsers.at(i)->getScore();
			}

			scoremsg = "You got it right! ";
			
		}
		else
		{
			scoremsg = "Wrong answer, boo. ";
		}
	
		scoremsg += "Your score is: ";
		char scorestr [2];
		_itoa_s(quizUsers.at(i)->getScore(), scorestr, 10);
		scoremsg += scorestr;
	
		whisper( quizUsers.at(i)->getSessionID(), scoremsg.c_str(), 100, 0, 100, 0, 0 );
	}
}

/** 
\fn void ParticipantManager::broadcastTopScores()
\brief Broadcasts the top scores and players who achieved it
*/
void ParticipantManager::broadcastTopScores()
{
	std::string top = "The top score is ";
	char scorestr [2];
	_itoa_s(topScore, scorestr, 10);
	top += scorestr;
	top += " achieved by";

	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getScore() == topScore )
		{
			top += " ";
			top += quizUsers.at(i)->getName(); 
		}
		
	}

	top += "!";

	broadcast(top.c_str(), 100, 0, 0, 1, 0 );				
	std::cout << top << std::endl;
}

/** 
\fn void ParticipantManager::setPlayerName( int session, std::string name )
\brief Sets the player name
\param session Session ID of the player
\param name Name of the player
*/
void ParticipantManager::setPlayerName( int session, std::string name )
{
	std::cout << "setting player name: " << name << " for session " << session << std::endl;
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getSessionID() == session )
		{
			
			quizUsers.at(i)->setName(name);
		}
	}
}


/** 
\fn std::string ParticipantManager::getPlayerName( int session )
\brief Gets the name of the player
\param session Session ID of the player
\return Name of the player
*/
std::string ParticipantManager::getPlayerName( int session )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getSessionID() == session )
			return quizUsers.at(i)->getName();
	}

	return NULL;
}

/** 
\fn void ParticipantManager::reset()
\brief Resets all variables for the next quiz game. 
*/
void ParticipantManager::reset()
{
	removeAllUsers();
	topScore = 0; 
	startingPlayerSID = -1;
}
