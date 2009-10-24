#ifndef _QUIZBOT_H_
#define _QUIZBOT_H_

#include "aw.h" //include Activeworld header file
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string> 
#include <Vector>
#include "Vect2D.h"
#include "ParticipantManager.h"
#include "QuizParticipant.h" 
#include "QuizPage.h" 
#include "Timer.h" 

enum BotState { QUIZBOT_IDLE, QUIZBOT_REGISTRATION, QUIZBOT_INPROGRESS };
class QuizBot
{

public:
	QuizBot(void);
	~QuizBot(void);

	void init(); 
	void createBot( std::string botName, int x, int y, int z );
	void createHUD( int session ); 

	//event handlers
	void onAvatarAdd(); 
	void onAvatarSpeak();
	void onAvatarChange(); 
	void onAvatarClick(); 
	void onAvatarHUDClick(); 

	bool AddPlayer( int speakerSession, std::string message );
	void QuizRound();

private:
	ParticipantManager users; 
	BotState quizState; 
	QuizPage quizPage; 
};

#endif