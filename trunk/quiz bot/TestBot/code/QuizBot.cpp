#include "QuizBot.h"

QuizBot::QuizBot(void)
{
}

QuizBot::~QuizBot(void)
{
}

void QuizBot::init()
{
	int rc;
	
	if (rc = aw_init (AW_BUILD)) 
	{
		printf ("Unable to initialize API (reason %d)\n", rc);
		exit (1);
	}

	//register event handlers
	/*aw_event_set(AW_EVENT_AVATAR_ADD, onAvatarAdd );
	aw_event_set(AW_EVENT_CHAT, onAvatarSpeak );
	aw_event_set(AW_EVENT_AVATAR_CHANGE, onAvatarChange); 
	aw_event_set(AW_EVENT_AVATAR_CLICK, onAvatarClick); 
	aw_event_set(AW_EVENT_HUD_CLICK, onAvatarHUDClick); */
}

void QuizBot::onAvatarAdd () //event handler when an user enters into the world
{
}

void QuizBot::onAvatarSpeak()
{
	//printf ("%s %s %s\n", aw_string (AW_AVATAR_NAME),
	//chat_type[aw_int (AW_CHAT_TYPE)], aw_string (AW_CHAT_MESSAGE));
	int speakerSession = aw_int( AW_CHAT_SESSION ); 

	if ( aw_int(AW_CHAT_TYPE) == AW_CHAT_WHISPER )
	{		
		std::string message = aw_string(AW_CHAT_MESSAGE);
		//std::cout << aw_string(AW_AVATAR_NAME) << " " << speakerSession << " whispered to me!" << std::endl;
		//if user is registered
		

		switch ( quizState )
		{
			case QUIZBOT_IDLE:
			{				
				if ( AddPlayer( speakerSession, message ) )
				{
					//delete everyone else in the list
					users.removeAllUsers();

					users.setUser( speakerSession, QUIZPLAYER_REGISTERED ); 
					
					quizState = QUIZBOT_REGISTRATION;
					users.setStartingPlayer( speakerSession );
					aw_whisper( speakerSession, "You are the starting player. Click on me when you would like to begin the quiz for everyone.");
					aw_say( "Join the quiz game starting now at Level 2!");
				}			
				
				break;
			}

			case QUIZBOT_REGISTRATION:
			{	
				// check if the player is the starting player
				if ( speakerSession == users.getStartingPlayer() )
				{
					if (( message == "Y" || message == "y" ) && users.getState(users.getStartingPlayer()) == QUIZPLAYER_START )
					{ 
						//start game
						users.broadcast( "Game started!" );
						quizState = QUIZBOT_INPROGRESS;
					}
					else
					{
						users.setState( speakerSession, QUIZPLAYER_REGISTERED );
						std::string str = "Please wait a moment while ";
						str += aw_string (AW_AVATAR_NAME);
						str += " gets the game started!";
						users.broadcast( str );
					}
				}
				else
				{
					AddPlayer( speakerSession, message );
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

bool QuizBot::AddPlayer( int speakerSession, std::string message )
{
	int userExists = users.userExists( speakerSession );

	if ( userExists == -1 ) //if the user isn't on the list, he hasn't clicked the bot yet
		return false;

	std::cout << "AddPlayer: playerstate = " << users.getState( speakerSession ) << std::endl;
	if ( users.getState( speakerSession ) != QUIZPLAYER_CLICKED ) //the player is already registered
	{
		aw_whisper( speakerSession , "Please wait for the game to start.");
		return false;
	}

	if ( message == "Y" || message == "y" )
	{
		std::cout << aw_string(AW_AVATAR_NAME) << " signed up \n";
		aw_whisper( speakerSession , "You have signed up for the quiz!");
		users.setUser( speakerSession, QUIZPLAYER_REGISTERED );
		users.print();
		return true;
	}

	else if ( message == "N" || message == "n" )
	{
		users.removeUser( speakerSession );
		aw_whisper( speakerSession , "Alrighty then.");
		return false;
	}
	return false;
	
}

void QuizBot::onAvatarClick()
{
	int clicker = aw_int( AW_AVATAR_SESSION ); 
	
	//bot got clicked on
	if ( aw_int(AW_CLICKED_SESSION) == aw_session() )
	{
		std::cout << aw_string(AW_AVATAR_NAME) << " " << clicker << " clicked on me! \n";
		//check if user exists in the participants list
		int userExists = users.userExists( clicker ); 

		switch (quizState)
		{
			case QUIZBOT_IDLE:
			{			
				aw_whisper( clicker, "Hello. Would you like to begin the quiz? (y/n)");
				users.setUser( clicker, QUIZPLAYER_CLICKED );			

				break;
			}

			case QUIZBOT_REGISTRATION:
			{
				if ( userExists == -1 ) //new player joins
				{
					aw_whisper( clicker, "Hello. Would you like to join the quiz? (y/n)");
					users.setUser( clicker, QUIZPLAYER_CLICKED );
				}
				
				else if ( users.getState(clicker) == QUIZPLAYER_REGISTERED ) // the clicker is registered
				{
					if ( users.getStartingPlayer() == clicker ) 
					{
						aw_whisper( clicker, "You are the starting player. Would you like to start the quiz now for everyone? (y/n)");
						users.setState( clicker, QUIZPLAYER_START );
					}	
					else
					{
						aw_whisper( clicker, "Please wait for the game to start.");
					}

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

void QuizBot::onAvatarChange()
{	
	Vect2D myPos; 
	myPos.SetXY( (float)aw_int(AW_MY_X), (float)aw_int(AW_MY_Y) );
	
	//check the distance of the avatars from the bot 
	if ( aw_int(AW_AVATAR_SESSION) != aw_session() )
	{
		
	//	std::cout << aw_int(AW_MY_X) << "\n";
	//	std::cout << aw_int(AW_AVATAR_SESSION) << " is now at " <<  
	//		aw_int(AW_AVATAR_X) << " " << aw_int (AW_AVATAR_Y) << " " <<  aw_int (AW_AVATAR_Z) << "\n" ;
	}
}

void QuizBot::onAvatarHUDClick()
{
	aw_hud_destroy(	aw_int(AW_HUD_ELEMENT_SESSION),	aw_int(AW_HUD_ELEMENT_ID)); 
}

void QuizBot::createHUD( int session )
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

void QuizBot::createBot( std::string botName, int x, int y, int z )
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

void QuizBot::QuizRound()
{
	//retrieve a question 
	QuizQuestion *q = quizPage.getNextQuestion();
	if ( q != NULL )
	{
		users.broadcast( q->getQuestion() );
		
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
			users.broadcast( msg );
		}

		//wait for 10 seconds for the players to answer
		aw_wait(10000);

		users.broadcast("Time's up!");				
	}
	else //no more questions
	{
		quizPage.reset();
		users.broadcast( "The quiz is over! Thank you for playing." );
		quizState = QUIZBOT_IDLE;
	}					
}