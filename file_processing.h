#ifndef FILE_PROCESSING_H_   /* Include guard */
#define FILE_PROCESSING_H_
#include <stdio.h>
#include <stdbool.h>
FILE* batch;
/*
	history file basic functions' prototypes
*/
void read_history_file();
void write_history_file(char *line);

/*
	log file basic functions' prototypes
*/
void read_log_file();
void write_log_file();

/*
	CommandsBatch file basic functions' prototypes
*/
bool open_commands_batch_file(char *line);
void close_commands_batch_file();

#endif // FILE_PROCESSING_H_
