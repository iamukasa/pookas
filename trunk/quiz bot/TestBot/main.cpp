#include "aw.h" //include Activeworld header file
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string> 
#include <Vector>
#include "Vect2D.h"
#include "ParticipantManager.h"
#include "QuizParticipant.h" 

void init(); 
void createBot( std::string botName, int x, int y, int z );
void createHUD( int session ); 

//event handlers
void onAvatarAdd(); 
void onAvatarSpeak();
void onAvatarChange(); 
void onAvatarClick(); 
void onAvatarHUDClick(); 

ParticipantManager users; 
enum BotState { QUIZBOT_IDLE, QUIZBOT_INPROGRESS };
BotState quizState; 

int main (int argc, char *argv[])
{
	std::cout << "Greeter Bot" << std::endl;
	
	init();
	createBot("SomeBot", 0, 0, 0);
	quizState = QUIZBOT_IDLE; 

	/* main event loop */
	while (!aw_wait (-1)) //wait for event to handle, can set the bot
	//behavior here
	;
	/* close everything down */
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
}

void onAvatarAdd () //event handler when an user enters into the world
{
}

void onAvatarSpeak()
{
	//printf ("%s %s %s\n", aw_string (AW_AVATAR_NAME),
	//chat_type[aw_int (AW_CHAT_TYPE)], aw_string (AW_CHAT_MESSAGE));
	int avatarSession = aw_int( AW_AVATAR_SESSION ); 

	if ( aw_int(AW_CHAT_TYPE) == AW_CHAT_WHISPER )
	{		
		std::string message = aw_string(AW_CHAT_MESSAGE);
		
		//if user is registered
		if ( users.userExists( avatarSession ) != -1 )
		{
			PlayerState state = users.getState( avatarSession );
			std::cout << state << "\n";

			if  (  state == QUIZPLAYER_CLICKED )
			{
				if ( message == "Y" || message == "y" )
				{
					std::cout << aw_string(AW_AVATAR_NAME) << " signed up \n";
					users.setUser( avatarSession, QUIZPLAYER_REGISTERED ); 
					aw_whisper( avatarSession , "You have signed up for the quiz!");

					if ( quizState == QUIZBOT_IDLE )
					{
						quizState = QUIZBOT_INPROGRESS;
						users.SetStartingPlayer( avatarSession );
					}
				}

				else if ( message == "N" || message == "n" )
				{
					users.removeUser( avatarSession );
					aw_whisper( avatarSession , "Alrighty then.");
				}
			}
				
		}
	}
}

void onAvatarClick()
{
	//bot got clicked on
	if ( aw_int(AW_CLICKED_SESSION) == aw_session() )
	{
		std::cout << aw_string(AW_AVATAR_NAME) << " clicked on me! \n";
		
		if ( users.userExists( aw_int(AW_AVATAR_SESSION) ) == -1 ) 
		{
			//send message to the user
			aw_whisper(aw_int(AW_AVATAR_SESSION), "Hello. Would you like to register for the quiz? (y/n)");
			users.setUser( aw_int(AW_AVATAR_SESSION), QUIZPLAYER_CLICKED );
		}
		else
		{
			aw_whisper(aw_int(AW_AVATAR_SESSION), "You have already signed up.");
		}
	}
}

void onAvatarChange()
{	
	if ( aw_int(AW_AVATAR_SESSION) != aw_session() )
	{
	//	std::cout << aw_int(AW_MY_X) << "\n";
	//	std::cout << aw_int(AW_AVATAR_SESSION) << " is now at " <<  
	//		aw_int(AW_AVATAR_X) << " " << aw_int (AW_AVATAR_Y) << " " <<  aw_int (AW_AVATAR_Z) << "\n" ;
	}
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

void createBot( std::string botName, int x, int y, int z )
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
	aw_int_set (AW_MY_X, x); //w
	aw_int_set (AW_MY_Y, y);
	aw_int_set (AW_MY_Z, z); //n
	aw_int_set (AW_MY_YAW, 2250); //facing

	if (rc = aw_state_change ()) 
	{ 
		//change bot state to let it appear in the world
		printf ("Unable to change state (reason %d)\n", rc);
		
	}
}