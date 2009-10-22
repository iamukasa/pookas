#include "ParticipantManager.h"

ParticipantManager::ParticipantManager(void)
{
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
		std::cout << "Session ID : " << p->getSessionID() << std::endl;
		quizUsers.push_back(p);		
		//std::cout << "Added user " << session << " Num = " << quizUsers.size(); 
	}

	Print();
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
	Print();
}

//returns the index into the participants vector if exists, -1 otherwise
int ParticipantManager::userExists( int session )
{
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		std::cout << "Searching user" << session << " i= " << quizUsers.at(i)->getSessionID(); 
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
}

void ParticipantManager::Print()
{
	std::cout << "~~" << std::endl;
	for ( unsigned int i = 0; i < quizUsers.size(); i++ )
	{
		std::cout << quizUsers.at(i)->getSessionID() << " " << quizUsers.at(i)->getState() << std::endl; 
	}
	std::cout << "~~" << std::endl;

}

void ParticipantManager::SetStartingPlayer( int session )
{
	startingPlayerSID = session; 
}

int ParticipantManager::GetStartingPlayer()
{
	return startingPlayerSID;
}
