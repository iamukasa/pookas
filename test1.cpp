#include "stdafx.h"
#include "aw.h"
#include <stdio.h>
#include <stdlib.h>

void handle_avatar_add(void);

int main()
{
	aw_init(AW_BUILD);
	aw_event_set(AW_EVENT_AVATAR_ADD,handle_avatar_add);//install handler for avatar_add event
	aw_create("155.69.101.53", 5552, 0);
	aw_int_set(AW_LOGIN_OWNER,1);//login as owner
	aw_string_set(AW_LOGIN_PRIVILEGE_PASSWORD,"12345");
	aw_string_set(AW_LOGIN_APPLICATION,"SDK Sample Application #1");
	aw_string_set(AW_LOGIN_NAME,"StudentBot");
	aw_login();
	aw_enter("A_Pookas");
	aw_int_set(AW_MY_X,1);//set position 1W
	aw_int_set(AW_MY_Z,1);//set position 1N
	aw_int_set(AW_MY_YAW,2250);//face towards GZ
	aw_state_change();//change bot state to let it appear in the world

	//main event loop
	while(!aw_wait(-1))
	//behavior here
	;

	//close everything
	aw_destroy();
	aw_term();
	return 0;
}

void handle_avatar_add(void)
{
	char message[100];
	sprintf(message,"Hey %s",aw_string(AW_AVATAR_NAME));
	aw_say(message);
	printf("avatar_add: %s\n",aw_string(AW_AVATAR_NAME));
}

