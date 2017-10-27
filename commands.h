#ifndef COMMANDS_H_   /* Include guard */
#define COMMANDS_H_
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
bool back_ground;
int cnt_back_ground = 0;
/*
	- This function should be responsible for implementing the "cd" shell command
*/
int cd(char ** args);

/*
	- This function should be responsible for implementing the "echo" shell command
	- Typically should lookup any variable included in the message
*/
int echo(char* line);
int Exit (char **args);
int variable(char **args,char * line);
int history (char **args);
int fun_execv(char **args);
int login(char **args);
int launch (char ** args);
int execute(char **args ,char * line);
int  clear_screen(char ** args);
#endif // COMMANDS_H_
