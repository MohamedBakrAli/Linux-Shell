#include "commands.h"
#include "environment.h"
#include "file_processing.h"
#include "signal.h"
#include <unistd.h>

// buid in function
char *buildin_arg[] = {
    "cd",
    "history",
    "login",
    "exit",
    "clear"
};
int (*buildin_func[]) (char **) = {
  &cd,
  &history,
  &login,
  &Exit,
  &clear_screen
};
const int fun_cnt = 5;
int history (char **args)
{
    read_history_file();
    return 1;
}
int login(char **args)
{
    read_log_file();
    return 1;
}
int  clear_screen(char ** args)
{
    system("@cls||clear");
    return 1;
}
int variable(char **args,char * line)
{
    char * new_line = remove_qoutes(line);
    char * key = strtok(new_line,"=");
    char * value = strtok(NULL,"=");
    char * new_value;
    if (!check_variable(key)){
            printf("bash : invalid variable name\n");
        return 1;
    }
    else {
        new_value = malloc(sizeof(char) * (strlen(value) + 1) );
        strcpy(new_value,remove_qoutes(value));
    }
    set_variable(key,new_value);
//    printf("----------------\n");
//    print_all_variables();
//    printf("----------------\n");
    return 1;
}
int cd(char **args)
{
    if (args[1] != NULL && (strcmp(args[1],"~") != 0)){
        if (args[1][strlen(args[1]) -1] == '\\'){
            args[1][strlen(args[1]) -1] = ' ';
            strcat(args[1],args[2]);
        }
        if (args[1][0] == '~'){
            char * path = malloc(sizeof(char) * 1000);
            strcpy(path,home_path);
            int i;
            int len = strlen(home_path);
            for (i = 1;args[1][i] != '\0'; i++){
                path[len + i - 1] = args[1][i];
            }
            path[len + i - 1 ] = '\0';
            if (chdir(path) != 0) {
                perror("bash");
            }
        }
        else {
            if (chdir(args[1]) != 0) {
                perror("bash");
            }
        }
    }
    else {
        chdir(home_path);
    }
    return 1;
}
int echo(char *line)
{
    int i;
    for (i = 0 ;line[i] != '\0'; i++){
        if (line[i] == 'e'){
            i += 4;
            while (line[i] == ' '){
                i++;
            }
            break;
        }
    }
    for (i ;line[i] != '\0'; i++){
        if (line[i] != '\n' && line[i] != '\'' && line[i] != '"')
            printf("%c",line[i]);
    }
    printf("\n");
    return 1;
}

int Exit (char **args)
{
    return 0;
}
int execute(char **args ,char *line)
{
    int i;
    if (args[0] == NULL)
        return 1;
    for (i = 0; i < fun_cnt; i++){
        if (strcmp(args[0],buildin_arg[i]) == 0)
            return (*buildin_func[i])(args);
    }
    if (strcmp(args[0],"echo") == 0){
        return echo(line);
    }
    char * eq = strchr(args[0],'=');
    if (eq != NULL){
        return variable(args, line);
    }
    return launch(args);
}
int launch (char ** args)
{
    pid_t pid, wpid;
    int status;
    if (strcmp(args[get_length(args)-1], "&") == 0){
        back_ground = true;
        cnt_back_ground ++;

    }
    else {
        back_ground = false;
    }
    pid = fork();
    signal(SIGCHLD,write_log_file);
    if (pid == 0) {
    // Child process
        if (fun_execv(args) == -1) {
            perror("bash");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        // Error forking
        perror("bash");
    }
    else {
        // Parent process
        if (back_ground == false){
            do {
                wpid = waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
        else {
            printf("[%d] : %d\n",cnt_back_ground,pid);
        }
    }
    return 1;
}
int fun_execv(char **args)
{
    if (args[0][0]=='/'){
        if (execv(args[0],args) != -1){
            printf("bash : command not found\n");
            return 0;
        }
    }
    char* path = getenv("PATH");
    char * loc = strtok(path, ":");
    while(loc!=NULL){
            char * str = malloc(strlen(loc) + strlen(args[0]) + 2);
            strcpy(str,loc);
            strcat(str,"/");
            strcat(str,args[0]);

            if (access(str,F_OK) != -1){
                if (execv(str,args) != -1){
                    perror("bash");
                    return 0;
                }
            }
        loc = strtok(NULL,":");
        free(str);
    }
    return -1;
}
