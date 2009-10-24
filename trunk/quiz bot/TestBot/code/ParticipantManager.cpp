#include "ParticipantManager.h"

ParticipantManager::ParticipantManager(void)
{
	startingPlayerSID = -1;
}

ParticipantManager::~ParticipantManager(void)
{
}

void ParticipantManager::Destroy()
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		//delete
		delete quizUsers.at(i); 
	}
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
	print();
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


void ParticipantManager::setPlayerPos( int session, int x, int y )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getSessionID() == session )
			quizUsers.at(i)->setPos( x, y ); 
	}
}

Vect2D* ParticipantManager::getPlayerPos( int session )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		if ( quizUsers.at(i)->getSessionID() == session )
			return &quizUsers.at(i)->getPos(); 
	}
	
	return NULL;	
}

void ParticipantManager::broadcast( std::string message )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		aw_whisper( quizUsers.at(i)->getSessionID(), message.c_str() );
	}
}