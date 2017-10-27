#include "file_processing.h"
#include "environment.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/*
	history file section
*/
void read_history_file(){
    FILE* history;
    char * path = malloc(sizeof(char) * 1000);
    strcpy(path, project_path);
    strcat(path,"/history.txt");
    int cnt = 1;
    char buff[255];
    history = fopen(path, "r");
    if (history == NULL){
        printf("bash : history file is not found\n");
        return;
    }
    while(fgets(buff, 255, (FILE*)history)){
        printf("  %d : %s",cnt, buff );
        cnt++;
    }
   fclose(history);
}

void write_history_file(char *line){
    bool flag = true;
    int i;
    for (i = 0;line[i] != '\0';i++){
        if (line[i] != ' ' && line[i] != '\n'){
            flag = false;
            break;
        }
    }
    // empty line do't write in the history file
    if (flag)
        return;
    char * path = malloc(sizeof(char) * 1000);
    strcpy(path, project_path);
    strcat(path,"/history.txt");
    FILE* history;
    history = fopen(path, "a");
    fprintf(history,"%s",line);
    fclose(history);
}

/*
	log file section
*/

void read_log_file()
{
	FILE* log;
    char * path = malloc(sizeof(char) * 1000);
    strcpy(path, project_path);
    strcat(path,"/login.txt");
    int cnt = 1;
    char buff[255];
    log = fopen(path, "r");
    if (log == NULL){
        printf("bash : longin file is not found\n");
        return;
    }
    while(fgets(buff, 255, (FILE*)log)){
        printf("%d : %s",cnt, buff );
        cnt++;
    }
   fclose(log);
}

void write_log_file()
{
	FILE* log;
    char * path = malloc(sizeof(char) * 1000);
    strcpy(path, project_path);
    strcat(path,"/log.txt");
    log = fopen(path, "a");
    pid_t pid;
    pid = wait(NULL);
    fprintf(log,"child process[%d] : terminated\n",pid);
    fclose(log);
}


/*
	CommandsBatch file section
*/

bool open_commands_batch_file(char * path)
{
	batch = fopen(path,"r");

	if (batch == NULL){
        printf("bash : batch file is not found\n");
        return false;
    }
    return true;
}

void close_commands_batch_file()
{
	fclose(batch);
}
