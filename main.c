#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "variables.h"
#include "environment.h"
#include "file_processing.h"
int main(int argc, char *argv[])
{
    setup_environment();
    if( argc > 1 ){
        if (open_commands_batch_file(argv[1])){
            start(true);
        }
        start(false);
    }
    else{
        start(false);
    }
    return EXIT_SUCCESS;
}

void start(bool read_from_file)
{
    chdir(home_path);
	if(read_from_file){
		shell_loop(true);
	}
	else{
		shell_loop(false);
	}
}

void shell_loop(bool input_from_file)
{
	bool from_file = input_from_file;
    char* line ;

    char input[10];
    int status = 1;
	while(status != 0){
        line = malloc(sizeof(char) * 1000);
		if(from_file){
			//read next instruction from file
            while (fgets(line, 100, (FILE*)batch) && status != 0){
                line[strlen(line) -1] = '\0';
                printf("%s\n",line);
                status = run_command(line);
            }
			// if end of file {from_file = fa   lse; continue;}
                from_file = false;
                close_commands_batch_file();
		}
		else{
			//read next instruction from console
			printf("\033[22;32mshell >> \033[0m");
			line = read_line();
            status = run_command(line);
		}
        // free memory location
        free(line);

	}
}
int run_command(char * line){
    int len = check_len(line);
      char **args;
    if (len > 512){
        printf("bash : a very long command line\n");
        return 1;
    }
    if (!check_qoutes(line)){
       printf("bash : missing a qoute in the command line\n");
        return 1;
    }
    // empty line
    if (len == 0)
        return 1;
    // save command to history file
    write_history_file(line);
    char *modified_line = malloc(sizeof(char) * 1000);
    // set the value of all variable in the command
    modified_line = generate_variables_values(line);
            //printf("%s#\n",modified_line);
    //parse your command here1
    args = parse_command(modified_line);
    //commant comand line
    if (args[0][0] == '#')
        return 1;
    //execute your command here
    int status = execute(args,modified_line);
    free(modified_line);
    free(args);
    return status;
}
