#include "command_parser.h"


char ** parse_command( char * line)
{
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;
    char * line_cope = malloc(sizeof(char)*(strlen(line)+1));
    strcpy(line_cope,line);
    if (!tokens) {
    fprintf(stderr, "bash : allocation error\n");
    exit(EXIT_FAILURE);
    }

    token = strtok(line_cope, LSH_TOK_DELIM);
    while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "bash : allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
int get_length(char ** args)
{
    int len = 0;
    while(args[len] != NULL)
        len ++;
    return len;
}
char *read_line(void)
{
    char *line = NULL;
    ssize_t bufsize = 0; // have getline allocate a buffer for us
    getline(&line, &bufsize, stdin);
    return line;
}
int check_len(char * line)
{
    int cnt = 0;
    int i;
    for (int i = 1; line[i] != '\0'; i++){
        if (!(line[i] == ' ' && line[i-1] == ' ')){
            cnt++;
        }
    }
    if (line[0] == ' ')
        cnt --;
    return cnt;
}
bool check_qoutes(char * var)
{
    int i;
    int cnt_single_qoutes = 0;
    int cnt_double_qoutes = 0;
    for (i=0; var[i] != '\0'; i++){
         if (var[i] == '\'')
            cnt_single_qoutes ++;
        else if (var[i] == '"')
            cnt_double_qoutes ++;
    }
     if ((cnt_double_qoutes % 2 != 0) || cnt_single_qoutes % 2 != 0)
        return false;
    return true;
}
