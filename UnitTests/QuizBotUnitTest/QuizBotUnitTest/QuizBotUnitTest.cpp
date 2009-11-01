#include "QuizBotUnitTest.h"

QuizBotUnitTest::QuizBotUnitTest(void)
{
}

QuizBotUnitTest::~QuizBotUnitTest(void)
{
}


/** 
\fn int botStart (char *htmldata)
\brief Main bot function where execution starts and ends. 
\param htmldata The string containing HTML format quiz data 

Initialises and shuts down ActiveWorlds and the bot.
Sets the position of the answer panels.
Contains a main loop that triggers every second. 
When the bot is IN_PROGRESS, this main loop calls quizRound().
*/
int QuizBotUnitTest::botStart (char *filename)
{
	//initialize quiz questions
	quizPage.loadHTMLDataFromFile(filename);

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

/** 
\fn void init()
\brief Initialises activeworlds api, registers event handlers
*/
void QuizBotUnitTest::init()
{
	int rc;
	
	if (rc = aw_init (AW_BUILD)) 
	{
		printf ("Unable to initialize API (reason %d)\n", rc);
		exit (1);
	}

	//register event handlers
//	aw_event_set(AW_EVENT_CHAT, onAvatarSpeak );	
//	aw_event_set(AW_EVENT_AVATAR_CLICK, onAvatarClick); 
}

/** 
\fn void destroy()
\brief Shutdown function called when execution ends. 
*/
void QuizBotUnitTest::destroy()
{
	for ( unsigned int i = 0; i < panelPos.size(); i++ )
	{
		delete panelPos.at(i);
	}

	users.destroy();
}

/** 
\fn void onAvatarSpeak()
\brief Called when an avatar speaks to another. 

Checks if the speaker is speaking to the bot. 
IDLE - Add starting player, and move state to REGISTRATION.
REGISTRATION - Add other players to the quiz.
*/
void QuizBotUnitTest::onAvatarSpeak( int speakerSession, std::string name, std::string message )
{
	if ( message == "password" ) //shut down the bot
	{
		contin = false; 
		return;
	}

	switch ( quizState )
	{
		case QUIZBOT_IDLE: //nobody decided to start a quiz game yet
		{				
			if ( addPlayer( speakerSession, name, message ) )
			{
				//delete everyone else in the list in case multiple people clicked but didn't reply y/n
				users.removeAllUsers();

				users.setUser( speakerSession, QUIZPLAYER_REGISTERED ); 
				users.setPlayerName( speakerSession, name );					
				users.setStartingPlayer( speakerSession );
				ParticipantManager::whisper(speakerSession,	
					"You are the starting player. Click on me when you would like to begin the quiz for everyone." ,
					0, 100, 0, 0, 0);
				
				aw_say( "[Announcement] Join the quiz game starting now at Level 2!");

				//advance the bot state to registration
				quizState = QUIZBOT_REGISTRATION;
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
				addPlayer( speakerSession, name, message );
			}
			
			break;
		}

		case QUIZBOT_INPROGRESS:
		{
			break; 
		}
		
	}
}

/** 
\fn bool addPlayer( int speakerSession, std::string name, std::string message )
\brief Adds player to the quiz.
\param speakerSession Session ID of the player who wants to join
\param name Name of the player who wants to join
\param message The player's whispered message to the bot.

Checks if the speaker is whispering "y/n" to the bot and adds the player accordingly.
*/
bool QuizBotUnitTest::addPlayer( int speakerSession, std::string name, std::string message )
{
	int userExists = users.userExists( speakerSession );

	if ( userExists == -1 ) //if the user isn't on the list, he hasn't clicked the bot yet
		return false;

	if ( users.getState( speakerSession ) != QUIZPLAYER_CLICKED ) //the player is already registered
	{
		ParticipantManager::whisper(speakerSession , "Please wait for the game to start.", 0, 100, 0, 0, 0);

		return false;
	}

	if ( message == "Y" || message == "y" )
	{
		//std::cout << aw_string(AW_AVATAR_NAME) << " signed up \n";
		ParticipantManager::whisper(speakerSession , "You have signed up for the quiz!", 0, 100, 0, 0, 0);
		users.setUser( speakerSession, QUIZPLAYER_REGISTERED );
		users.setPlayerName( speakerSession, name );
		//users.print();

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


/** 
\fn void onAvatarClick()
\brief Called when an avatar is clicked

Checks if the player clicked on the bot.
IDLE - Bot asks if the player wants to start a new quiz. 
REGISTRATION - Bot asks if the player wants to join.
IN_PROGRESS - Notifies clicker that a quiz is in progress. 
*/
void QuizBotUnitTest::onAvatarClick( int clicker )
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

/** 
\fn void createBot( std::string botName, float x, float y, float z )
\brief Called to create a bot. 

\param botName Name of the bot
\param x x-coordinate
\param y y-coordinate
\param z z-coordinate

Creates a bot and connects to ActiveWorlds. Does not support multiple instances currently.
*/
void QuizBotUnitTest::createBot( std::string botName, float x, float y, float z )
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

/** 
\fn void createBot( std::string botName, float x, float y, float z )
\brief Defines each round of the quiz when the bot is IN_PROGRESS.

Called every tick when the bot is IN_PROGRESS.
Gets questions and answers each round, checks the answers when time is up, and increments player score accordingly.
Resets the quiz when all the questions are used. 
*/
void QuizBotUnitTest::quizRound()
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
			users.broadcast( a->at(i), 0, 0, 0, 1, 0 );
		}

		//wait for 10 seconds for the players to answer
		aw_wait(10000);
		
		users.broadcast("Time's up!", 100, 0, 100, 0, 0 );				
		
		//check answers
		//users.checkAnswers( *panelPos.at( q->getCorrectAnswer() ) , 200);

		//broadcast the correct answer
		std::string correct = "The correct answer was ";
		correct += q->getAnswers()->at( q->getCorrectAnswer() );
		users.broadcast( correct, 0, 100, 0, 1, 0 );


	}
	else //no more questions
	{	
		//broadcast the top scores
		//users.broadcastTopScores();
		//users.broadcast( "The quiz is over! Thank you for playing.", 100, 0, 100, 1, 0 );
		
		//reset everything
		quizPage.reset();
		users.reset();
		quizState = QUIZBOT_IDLE;
	}					
}
