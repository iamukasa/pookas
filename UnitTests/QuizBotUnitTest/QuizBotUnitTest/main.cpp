#include <Basic.h>
#include "ParticipantManager.h"
#include "QuizPage.h" 
#include "QuizBotUnitTest.h"
#include "QuizPage.h"

ParticipantManager p; 
CU_pSuite pSuite = 0;
static FILE* temp_file = NULL;

int init_suite1(void);
int clean_suite1(void);

void testPManagerAddPlayer();
void testPManagerUserExists();
void testPManagerGetStartingPlayer();
void testBotHTMLRead();
void testBotQuizStart();
void testBotAddPlayer();
void testBotQuizRound();

int main()
{
	//add user
	p.setUser( 1, QUIZPLAYER_CLICKED );
	p.setUser( 10, QUIZPLAYER_CLICKED );
	p.setStartingPlayer(1);

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   if (
	   ( NULL == CU_add_test( pSuite, "testPManagerAddPlayer", testPManagerAddPlayer ) ) ||
	   ( NULL == CU_add_test( pSuite, "testPManagerUserExists", testPManagerUserExists ) ) ||
	   ( NULL == CU_add_test( pSuite, "testPManagerGetStartingPlayer", testPManagerGetStartingPlayer ) ) ||
		( NULL == CU_add_test( pSuite, "testBotHTMLRead", testBotHTMLRead ) ) ||
		( NULL == CU_add_test( pSuite, "testBotQuizStart", testBotQuizStart ) ) ||
		( NULL == CU_add_test( pSuite, "testBotAddPlayer", testBotAddPlayer ) ) ||
		( NULL == CU_add_test( pSuite, "testBotQuizRound", testBotQuizRound ) )
	   )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();


}

int init_suite1(void)
{
   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}

int clean_suite1(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}

void testPManagerAddPlayer()
{
	CU_ASSERT_EQUAL( p.getState(1), QUIZPLAYER_CLICKED );
}

void testPManagerUserExists()
{
	CU_ASSERT_EQUAL( p.userExists(2), -1); 
}

void testPManagerGetStartingPlayer()
{
	CU_ASSERT_EQUAL( p.getStartingPlayer(), 1); 
}

void testBotHTMLRead()
{
	QuizPage p;
	p.loadHTMLDataFromFile("quiz.html");

	CU_ASSERT_EQUAL( p.questions.size(), 3 ); 
}

void testBotQuizStart()
{
	QuizBotUnitTest b; 
	b.quizState = QUIZBOT_IDLE; 
	
	b.onAvatarClick( 1); //player 1 clicks on the bot
	b.onAvatarSpeak(1, "MyName", "y" ); //player 1 signs up
	CU_ASSERT_EQUAL( b.quizState, QUIZBOT_REGISTRATION ); //the bot goes to registration state
	CU_ASSERT_EQUAL( b.users.quizUsers.at(0)->getSessionID(), 1 ); //there should be 1 player in the player list
	CU_ASSERT_EQUAL( b.users.getStartingPlayer(), 1 ); //starting player should be 1.

	//the following code asserts that the player has to click on the bot before they can start the quiz or not
	//wrong case because the player didn't click on the bot again 

	b.onAvatarClick( 1); //starting player clicks on the bot
	CU_ASSERT_EQUAL( b.users.quizUsers.at(0)->getState(), QUIZPLAYER_STARTER );
	b.onAvatarSpeak(1, "MyName", "n" );  //starting player doesn't want to start quiz
	CU_ASSERT_EQUAL( b.quizState, QUIZBOT_REGISTRATION );
	b.onAvatarSpeak(1, "MyName", "y" ); //starting player starts quiz but didn't click on the bot again
	CU_ASSERT_EQUAL( b.users.quizUsers.at(0)->getState(), QUIZPLAYER_REGISTERED );
	CU_ASSERT_EQUAL( b.quizState, QUIZBOT_REGISTRATION ); //bot goes to in progress

	//correct case
	b.onAvatarClick( 1); //starting player clicks on the bot
	CU_ASSERT_EQUAL( b.users.quizUsers.at(0)->getState(), QUIZPLAYER_STARTER );
	b.onAvatarSpeak(1, "MyName", "y" ); //starting player starts quiz
	CU_ASSERT_EQUAL( b.users.quizUsers.at(0)->getState(), QUIZPLAYER_STARTER );
	CU_ASSERT_EQUAL( b.quizState, QUIZBOT_INPROGRESS );
}

void testBotAddPlayer()
{
	QuizBotUnitTest b; 
	b.quizState = QUIZBOT_IDLE; 
	
	b.onAvatarClick( 1); //player 1 clicks on the bot
	b.onAvatarSpeak(1, "MyName", "y" ); //player 1 signs up
	CU_ASSERT_EQUAL( b.quizState, QUIZBOT_REGISTRATION ); //the bot goes to registration state
	CU_ASSERT_EQUAL( b.users.quizUsers.at(0)->getSessionID(), 1 ); //there should be 1 player in the player list
	CU_ASSERT_STRING_EQUAL( b.users.quizUsers.at(0)->getName().c_str(), "MyName" );
	CU_ASSERT_EQUAL( b.users.getStartingPlayer(), 1 ); //starting player should be 1.

	//test adding another player to the quiz 
	b.onAvatarClick(2); 
	b.onAvatarSpeak(2, "Name2", "y" ); 
	CU_ASSERT_EQUAL( b.quizState, QUIZBOT_REGISTRATION );
	CU_ASSERT_EQUAL( b.users.quizUsers.at(1)->getSessionID(), 2 ); //the second player should be 2. 
	CU_ASSERT_STRING_EQUAL( b.users.quizUsers.at(1)->getName().c_str(), "Name2" );
	CU_ASSERT_EQUAL( b.users.getStartingPlayer(), 1 ); //starting player should be 1. NOT 2. 
}

void testBotQuizRound()
{
	QuizBotUnitTest b; 
	b.quizPage.loadHTMLDataFromFile("quiz.html"); //load the HTML data 
	CU_ASSERT_EQUAL( b.quizPage.questions.size(), 3 ); 
	CU_ASSERT_EQUAL( b.quizPage.counter, 0 );
	b.quizRound(); //first question
	CU_ASSERT_EQUAL( b.quizPage.counter, 1 );
	b.quizRound(); //Second question
	CU_ASSERT_EQUAL( b.quizPage.counter, 2 );
	b.quizRound(); //third question
	CU_ASSERT_EQUAL( b.quizPage.counter, 3 );
	b.quizRound();  //reset when there's no more questions
	CU_ASSERT_EQUAL( b.quizPage.counter, 0 ); //reset the questions
	CU_ASSERT_EQUAL( b.users.quizUsers.size(), 0 ); //reset the user list
	CU_ASSERT_EQUAL( b.quizState, QUIZBOT_IDLE ); //bot goes back to idle state
}