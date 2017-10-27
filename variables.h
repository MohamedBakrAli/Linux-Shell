#ifndef VARIABLES_H_   /* Include guard */
#define VARIABLES_H_
#include <stdbool.h>
/*
	- This function should be responsible for getting the value of a variable
	- To execute commands, You must always search for the executable files
	  in the value returned by lookup_variable("PATH");
	- Your code must be dynamic and can handle any number of variables, However,
	  performance is not an issue since in practice we expect low number of variables,
	  as a tip: simple array lookup would be fine
*/
char* lookup_variable(char* key );

/*
	- This function should be responsible for setting the value of a variable
*/
void set_variable( char* key , char* value );


/*
	[OPTIONAL] Doesn't affect the code logic
	- This is a helper function to print all your variables
	- Might help much in the debugging or testing
*/
void print_all_variables( void );
/*
    -check the syntax of the variable name.
    -it must start by char[a-z] or [_] then you can put now chars[a-z] or numbers[0-9] or [_]
    or all of them. else it isnot valid name.
*/
bool check_variable(char * var);
/*
    - look up all variables and put their values
*/
char * generate_variables_values(char *line);
#endif // VARIABLES_H_
