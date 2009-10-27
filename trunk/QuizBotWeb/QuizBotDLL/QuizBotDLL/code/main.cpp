#include "aw.h" //include Activeworld header file
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
void init(); 
void createBot( std::string botName, float x, float y, float z );
void createHUD( int session ); 

//event handlers
void onAvatarAdd(); 
void onAvatarSpeak();
void onAvatarChange(); 
void onAvatarClick(); 
void onAvatarHUDClick(); 
void onBump(); 

bool addPlayer( int speakerSession, std::string name, std::string message );
void quizRound();
void destroy();

enum BotState { QUIZBOT_IDLE, QUIZBOT_REGISTRATION, QUIZBOT_INPROGRESS };

ParticipantManager users; 
BotState quizState; 
QuizPage quizPage; 
std::vector <Vect3D*> panelPos;
bool contin = true; 
int botStart (char *htmldata)
{
	std::cout << "Quiz Bot" << std::endl;
	std::cout << "HTML Data:\n" << htmldata << std::endl;

	//initialize quiz questions
	quizPage.loadHTMLData(htmldata);

	init();
	createBot("Quiz Bot", 4750, 815, -518);	
	quizState = QUIZBOT_IDLE; 
	
	//set the positions for the answer panels
	panelPos.push_back( new Vect3D(4200, 760, 82) ); //1
	panelPos.push_back( new Vect3D(4150, 760, -1118) ); //2
	panelPos.push_back( new Vect3D(5350, 760, -418) ); //3
	
	while (contin) //main event loop triggers every second
	{
		switch ( quizState )
		{
			case QUIZBOT_IDLE:
			{
				break;
			}

			case QUIZBOT_INPROGRESS:
			{
				quizRound();
				break;
			}

		}
		aw_wait (1000);
	}
	
	destroy();
	aw_destroy ();
	aw_term ();
	return 0;
}

void init()
{
	int rc;
	
	if (rc = aw_init (AW_BUILD)) 
	{
		printf ("Unable to initialize API (reason %d)\n", rc);
		exit (1);
	}

	//register event handlers
	aw_event_set(AW_EVENT_AVATAR_ADD, onAvatarAdd );
	aw_event_set(AW_EVENT_CHAT, onAvatarSpeak );
	aw_event_set(AW_EVENT_AVATAR_CHANGE, onAvatarChange); 
	aw_event_set(AW_EVENT_AVATAR_CLICK, onAvatarClick); 
	aw_event_set(AW_EVENT_HUD_CLICK, onAvatarHUDClick); 
	aw_event_set(AW_EVENT_OBJECT_BUMP, onBump); 
}

void destroy()
{
	for ( unsigned int i = 0; i < panelPos.size(); i++ )
	{
		delete panelPos.at(i);
	}
}

void onAvatarAdd () //event handler when an user enters into the world
{
}

void onAvatarSpeak()
{
	int speakerSession = aw_int( AW_CHAT_SESSION ); 

	if ( aw_int(AW_CHAT_TYPE) == AW_CHAT_WHISPER )
	{		
		std::string message = aw_string(AW_CHAT_MESSAGE);
		if ( message == "password" )
		{
			contin = false; 
			return;
		}

		switch ( quizState )
		{
			case QUIZBOT_IDLE:
			{				
				if ( addPlayer( speakerSession, aw_string(AW_AVATAR_NAME), message ) )
				{
					//delete everyone else in the list
					users.removeAllUsers();

					users.setUser( speakerSession, QUIZPLAYER_REGISTERED ); 
					users.setPlayerName( speakerSession, aw_string(AW_AVATAR_NAME) );

					quizState = QUIZBOT_REGISTRATION;
					users.setStartingPlayer( speakerSession );
					ParticipantManager::whisper(speakerSession,	
						"You are the starting player. Click on me when you would like to begin the quiz for everyone." ,
						0, 100, 0, 0, 0);
					
					aw_say( "[Announcement] Join the quiz game starting now at Level 2!");
				}			
				
				break;
			}

			case QUIZBOT_REGISTRATION:
			{	
				// check if the player is the starting player
				if ( speakerSession == users.getStartingPlayer() )
				{
					if (( message == "Y" || message == "y" ) && 
						users.getState(users.getStartingPlayer()) == QUIZPLAYER_STARTER )
					{ 
						//remove all players with state QUIZPLAYER_CLICKED
						users.removeAllWithState( QUIZPLAYER_CLICKED );

						//start game
						users.broadcast( "Game started!", 100, 0, 100, 1, 0 );
						quizState = QUIZBOT_INPROGRESS;
					}
					else
					{
						users.setState( speakerSession, QUIZPLAYER_REGISTERED );
						std::string str = "Please wait a moment while ";
						str += aw_string (AW_AVATAR_NAME);
						str += " gets the game started!";
						users.broadcast( str, 0, 1, 0, 0, 1 );
					}
				}
				else //not the starting player
				{
					//add the player
					addPlayer( speakerSession, aw_string(AW_AVATAR_NAME), message );
				}
				
				break;
			}

			case QUIZBOT_INPROGRESS:
			{
				break; 
			}
			
		}
				
		
	}
}

bool addPlayer( int speakerSession, std::string name, std::string message )
{
	int userExists = users.userExists( speakerSession );

	if ( userExists == -1 ) //if the user isn't on the list, he hasn't clicked the bot yet
		return false;

	std::cout << "AddPlayer: playerstate = " << users.getState( speakerSession ) << std::endl;
	if ( users.getState( speakerSession ) != QUIZPLAYER_CLICKED ) //the player is already registered
	{
		ParticipantManager::whisper(speakerSession , "Please wait for the game to start.", 0, 100, 0, 0, 0);

		return false;
	}

	if ( message == "Y" || message == "y" )
	{
		std::cout << aw_string(AW_AVATAR_NAME) << " signed up \n";
		ParticipantManager::whisper(speakerSession , "You have signed up for the quiz!", 0, 100, 0, 0, 0);
		users.setUser( speakerSession, QUIZPLAYER_REGISTERED );
		users.setPlayerName( speakerSession, name );
		users.print();

		//broadcast to everyone that the new player has joined. 
		std::string announce = name;
		announce += " has joined the game!";
		users.broadcast(announce, 0, 100, 0, 0, 0);
		return true;
	}

	else if ( message == "N" || message == "n" )
	{
		users.removeUser( speakerSession );
		ParticipantManager::whisper(speakerSession , "Alrighty then.", 0, 100, 0, 0, 0);
		return false;
	}
	
	return false;
}

void onAvatarClick()
{
	int clicker = aw_int( AW_AVATAR_SESSION ); 
	
	//bot got clicked on
	if ( aw_int(AW_CLICKED_SESSION) == aw_session() )
	{
		//check if user exists in the participants list
		int userExists = users.userExists( clicker ); 

		switch (quizState)
		{
			case QUIZBOT_IDLE:
			{			
				ParticipantManager::whisper(clicker , "Hello. Up for some quizzing today? (y/n)", 0, 100, 0, 1, 0);
				users.setUser( clicker, QUIZPLAYER_CLICKED );			
				
				break;
			}

			case QUIZBOT_REGISTRATION:
			{
				if ( userExists == -1 ) //new player joins
				{
					ParticipantManager::whisper(clicker , "Hello. Would you like to join the quiz? (y/n)", 0, 100, 0, 1, 0);
					users.setUser( clicker, QUIZPLAYER_CLICKED );
				}
				
				else if ( users.getState(clicker) == QUIZPLAYER_REGISTERED ) // the clicker is registered
				{
					if ( users.getStartingPlayer() == clicker ) 
					{
						ParticipantManager::whisper(clicker , 
							"You are the starting player. Would you like to start the quiz now for everyone? (y/n)", 
							0, 100, 0, 0, 0);
						users.setState( clicker, QUIZPLAYER_STARTER );
					}	
					else
					{
						ParticipantManager::whisper(clicker, "Please wait for the game to start.", 0, 100, 0, 0, 0);
					}

				}
				break;
			}

			case QUIZBOT_INPROGRESS:
			{
				ParticipantManager::whisper(clicker , "A quiz is in progress, please wait for the current game to finish.", 0, 100, 0, 1, 0);
				break;
			}
		}	
	}
}

void onAvatarChange()
{	
	
}

void onAvatarHUDClick()
{
	aw_hud_destroy(	aw_int(AW_HUD_ELEMENT_SESSION),	aw_int(AW_HUD_ELEMENT_ID)); 
}

void createHUD( int session )
{
	int rc;
	aw_int_set (AW_HUD_ELEMENT_TYPE, AW_HUD_TYPE_TEXT);
	aw_string_set (AW_HUD_ELEMENT_TEXT, "This is a HUD element");
	aw_int_set (AW_HUD_ELEMENT_ID, 1);
	aw_int_set (AW_HUD_ELEMENT_SESSION, session);
	aw_int_set (AW_HUD_ELEMENT_ORIGIN, AW_HUD_ORIGIN_CENTER);
	aw_float_set (AW_HUD_ELEMENT_OPACITY, 1.0f);
	aw_int_set (AW_HUD_ELEMENT_X, -100);
	aw_int_set (AW_HUD_ELEMENT_Y, -100);
	aw_int_set (AW_HUD_ELEMENT_Z, 1);
	aw_int_set (AW_HUD_ELEMENT_FLAGS, AW_HUD_ELEMENT_FLAG_CLICKS);
	aw_int_set (AW_HUD_ELEMENT_COLOR, 0xff0000); /* RGB (255, 255,0) */
	aw_int_set (AW_HUD_ELEMENT_SIZE_X, 200);
	aw_int_set (AW_HUD_ELEMENT_SIZE_Y, 200);
	
	if (rc = aw_hud_create ())
		printf ("Unable to create HUD element (reason %d)\n", rc);	

}

void onBump()
{
	std::cout << "Someone bumped into: " << aw_string(AW_OBJECT_MODEL) << std::endl;
}

void createBot( std::string botName, float x, float y, float z )
{
	int rc; 

	/* create bot instance */
	if (rc = aw_create ("155.69.101.53", 5552, 0)) 
	{ 
		//server to launch the bot, ip is 155.69.101.53, and port is 5552
		printf ("Unable to create bot instance (reason %d)\n", rc);
	}

	/* log bot into the universe */
	aw_int_set (AW_LOGIN_OWNER, 1); //citizen id of the administrator
	aw_string_set (AW_LOGIN_PRIVILEGE_PASSWORD, "12345"); //privilege password of administrator
	aw_string_set (AW_LOGIN_APPLICATION, "SDK Sample Application #1");
	aw_string_set (AW_LOGIN_NAME, botName.c_str()); //set bot name

	if (rc = aw_login ()) 
	{ //login to uniserver
		printf ("Unable to login (reason %d)\n", rc);
		//exit (1);
	}
	/* log bot into the world called "beta" */
	if (rc = aw_enter ("A_Pookas")) 
	{ 
		printf ("Unable to enter world (reason %d)\n", rc);		
	}

	/* announce our position in the world */
	aw_int_set (AW_MY_X, (int)x); //w
	aw_int_set (AW_MY_Y, (int)y);
	aw_int_set (AW_MY_Z, (int)z); //n
	aw_int_set (AW_MY_YAW, 900); //facing
	aw_int_set (AW_MY_TYPE, 62 );	
	aw_int_set (AW_MY_GESTURE, 1);

	if (rc = aw_state_change ()) 
	{ 
		//change bot state to let it appear in the world
		printf ("Unable to change state (reason %d)\n", rc);
		
	}
}

void quizRound()
{
	//retrieve a question 
	QuizQuestion *q = quizPage.getNextQuestion();
	if ( q != NULL )
	{
		users.broadcast( q->getQuestion(), 255, 0, 0, 1, 0 );
		
		//get the answers for the question
		std::vector <std::string>* a = q->getAnswers();
		for ( unsigned int i = 0; i < a->size(); i++ )
		{
			std::string msg;
			char optionNum [2]; // assume the number of questions will never be 3 digits
			_itoa_s(i+1, optionNum,10);
			msg += optionNum;
			msg += " ";
			msg += a->at(i);
	
			users.broadcast( msg, 0, 0, 0, 1, 0 );
		}

		//wait for 10 seconds for the players to answer
		aw_wait(10000);
		
		users.broadcast("Time's up!", 100, 0, 100, 0, 0 );				
		
		//check answers
		users.checkAnswers( *panelPos.at( q->getCorrectAnswer() ) , 200);

		//broadcast the correct answer
		std::string correct = "The correct answer was ";
		correct += q->getAnswers()->at( q->getCorrectAnswer() );
		users.broadcast( correct, 0, 100, 0, 1, 0 );


	}
	else //no more questions
	{	
		//broadcast the top scores
		users.broadcastTopScores();
		users.broadcast( "The quiz is over! Thank you for playing.", 100, 0, 100, 1, 0 );
	
		quizPage.reset();
		users.reset();
		quizState = QUIZBOT_IDLE;
	}					
}