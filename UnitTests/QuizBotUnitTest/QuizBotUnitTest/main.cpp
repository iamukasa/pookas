#include <Basic.h>
#include "ParticipantManager.h"

ParticipantManager p; 
CU_pSuite pSuite = 0;
static FILE* temp_file = NULL;

int init_suite1(void);
int clean_suite1(void);

void testAddPlayer();
void testUserExists();
void testGetStartingPlayer();

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
	   ( NULL == CU_add_test( pSuite, "testAddPlayer", testAddPlayer ) ) ||
	   ( NULL == CU_add_test( pSuite, "testUserExists", testUserExists ) ) ||
	   ( NULL == CU_add_test( pSuite, "testGetStartingPlayer", testGetStartingPlayer ) )
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

void testAddPlayer()
{
	CU_ASSERT_EQUAL( p.getState(1), QUIZPLAYER_CLICKED );
}

void testUserExists()
{
	CU_ASSERT_EQUAL( p.userExists(2), -1); 
}

void testGetStartingPlayer()
{
	CU_ASSERT_EQUAL( p.getStartingPlayer(), 1); 
}