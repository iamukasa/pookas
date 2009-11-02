#include "QuizParticipant.h"

QuizParticipant::QuizParticipant(void)
{
	score = 0;
	name = "";
}

QuizParticipant::QuizParticipant( int session )
{
	sessionID = session;
	state = QUIZPLAYER_CLICKED;
	score = 0;
}

QuizParticipant::~QuizParticipant(void)
{
}

void QuizParticipant::setState( PlayerState s )
{
	state = s; 
}

PlayerState QuizParticipant::getState()
{
	return state;
}

void QuizParticipant::setSessionID( int session )
{
	sessionID = session;
}

int QuizParticipant::getSessionID()
{
	return sessionID;
}

/** 
\fn bool QuizParticipant::checkCollision( Vect3D objPos, int radius )
\brief Sphere collision detection between a player and an object
\param objPos The position of the object
\param radius The size of the object 
\return Whether the player collided with the object 

When a player is within the radius of the object, detect as collided. 
*/
bool QuizParticipant::checkCollision( Vect3D objPos, int radius )
{
	//get this player's position
	if ( int rc = aw_avatar_location (NULL, sessionID, NULL) )
	{
		return false;
	}

	Vect3D playerPos( (float)aw_int(AW_AVATAR_X), (float)aw_int(AW_AVATAR_Y), (float)aw_int(AW_AVATAR_Z) );

	//check collision with the object pos
	float dist = Vect3D::Distance( playerPos, objPos );
	if ( dist <= radius )
	{
		return true;
	}

	return false;
}

void QuizParticipant::addScore()
{
	score+=1;
}

int QuizParticipant::getScore()
{
	return score;
}

void QuizParticipant::setName(std::string n)
{
	name = n;

}

std::string QuizParticipant::getName()
{
	return name;
}