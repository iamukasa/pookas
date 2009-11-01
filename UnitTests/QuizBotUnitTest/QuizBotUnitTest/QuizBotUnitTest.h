#ifndef _QUIZBOTUNIT_H
#define _QUIZBOTUNIT_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string> 
#include <Vector>
#include "Vect3D.h"
#include "ParticipantManager.h"
#include "QuizParticipant.h" 
#include "QuizPage.h" 
#include <windows.h>

enum BotState { QUIZBOT_IDLE, /**< Nobody has talked to the bot */
QUIZBOT_REGISTRATION, /**< Someone decided to start a quiz, and other players can join */
QUIZBOT_INPROGRESS /**< Quiz is in progress */
}; 

class QuizBotUnitTest
{
public:
	QuizBotUnitTest(void);
	~QuizBotUnitTest(void);

	void init(); 
	int botStart (char *htmldata);
	void createBot( std::string botName, float x, float y, float z );
	void createHUD( int session ); 
	void onAvatarSpeak( int speakerSession, std::string name, std::string message );
	void onAvatarClick( int clicker );
	bool addPlayer( int speakerSession, std::string name, std::string message );
	void quizRound();
	void destroy();

	ParticipantManager users; 
	BotState quizState; 
	QuizPage quizPage; 
	std::vector <Vect3D*> panelPos;
	bool contin;

};

#endif