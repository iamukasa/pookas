#include "ParticipantManager.h"

ParticipantManager::ParticipantManager(void)
{
	int topScore = 0;
	startingPlayerSID = -1;
}

ParticipantManager::~ParticipantManager(void)
{
}

void ParticipantManager::destroy()
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		//delete
		delete quizUsers.at(i); 
	}

	quizUsers.clear();
}

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

void ParticipantManager::setAllUsers ( PlayerState state )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		quizUsers.at(i)->setState(state);

	}

}

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

void ParticipantManager::removeAllUsers()
{
	quizUsers.clear();
	std::cout << "After clear\n";
}

void ParticipantManager::removeAllWithState( int state )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getState() == state )
		{
			quizUsers.erase(quizUsers.begin()+i, quizUsers.begin()+i+1 );
		}
	}
}

//returns the index into the participants vector if exists, -1 otherwise
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

PlayerState ParticipantManager::getState( int session )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getSessionID() == session )
			return quizUsers.at(i)->getState();
	}

	return QUIZPLAYER_INVALID;
}

void ParticipantManager::setState( int session, PlayerState state )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getSessionID() == session )
			quizUsers.at(i)->setState( state ); 
	}
}

void ParticipantManager::print()
{
	std::cout << "=======================" << std::endl;
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		std::cout << quizUsers.at(i)->getSessionID() << " " << quizUsers.at(i)->getState() << std::endl; 
	}
	std::cout << "=======================" << std::endl;

}

void ParticipantManager::setStartingPlayer( int session )
{
	startingPlayerSID = session; 
}

int ParticipantManager::getStartingPlayer()
{
	return startingPlayerSID;
}


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

void ParticipantManager::broadcastTopScores()
{
	std::string top = "The top score is ";
	char scorestr [2];
	_itoa_s(topScore, scorestr, 10);
	top += scorestr;
	top += " achieved by ";

	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getScore() == topScore )
			top += quizUsers.at(i)->getName(); 
	}

	top += "!";

	broadcast(top.c_str(), 100, 0, 0, 1, 0 );				

}

void ParticipantManager::setPlayerName( int session, std::string name )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getSessionID() == session )
			quizUsers.at(i)->setName(name);
	}
}

std::string ParticipantManager::getPlayerName( int session )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getSessionID() == session )
			return quizUsers.at(i)->getName();
	}

	return NULL;
}