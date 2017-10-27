#include "variables.h"
#include <stdio.h>
#include <string.h>

// value table
char value_table[1000][512];
// key table
char key_table[1000][512];
// counter of number of values saved in the shell
int cnt = 0;
int i;
char* lookup_variable(char* key )
{
	for (i = 0; i < cnt; i++){
        if (strcmp(key, key_table[i]) == 0) {
            return value_table[i];
        }
	}
	if (getenv(key) != NULL){
        return getenv(key);
	}
	return NULL;
}
bool check_variable(char * var){
    int i;
    if (var[0] != '_' && !(var[0] >= 'A' && var[0] <= 'Z') && !(var[0] >= 'a' && var[0] <= 'z'))
        return false;
    for (i = 0; var[i] != '\0'; i++){
        if (var[i] != '_' && !(var[i] >= 'A' && var[i] <= 'Z') && !(var[i] >= 'a' && var[i] <= 'z')
        && !(var[i] >= '0' && var[i] <= '9'))
            return false;

    }
    return true;
}
bool check_value(char * var){
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
char *remove_qoutes(char * old_str){
    char * new_str = malloc(sizeof(char) * strlen(old_str));
    int i,j=0;
    for (i=0;old_str[i] != '\0';i++){
    if (old_str[i] !='\'' && old_str[i] != '"')
    new_str[j++] = old_str[i];
    }
    new_str[j] ='\0';
    return new_str;
}
void set_variable(char* key ,char* value )
{
    for (i = 0;i < cnt ;i++){
        if (strcmp(key,key_table[i]) == 0){
            strcpy(value_table[i],value);
            return;
        }
    }
    strcpy(value_table[cnt],value);
    strcpy(key_table[cnt],key);
	cnt++;
	return;
}
void print_all_variables( void )
{
	printf("index\t\tkey\t\tvalue\n");
	for (i = 0;i < cnt ;i++){
        printf("%d:\t\t%s\t\t%s\n",i,key_table[i],value_table[i]);
	}
	return;
}
char * generate_variables_values(char *line){
        int i;
    char * new_line = malloc(sizeof(char) * 1000);
    for (i = 0; line[i] != '\0'; i++){
        if (line[i] == '$' && line[i+1] != '\0'){
            char * variable = malloc(sizeof(char) * 512);
            int j = 0;
            i++;
            if (line[i] == '_' || (line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z')){
                while (line[i] == '_' || (line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z')
                || (line[i] >= '0' && line[i] <= '9')){
                    variable[j++] = line[i++];
                }
                variable[j] = '\0';
                char * value = malloc(sizeof(char) * 512);
                value = lookup_variable(variable);
                if (value != NULL){
                    strcat(new_line,value);
                    //new_line[strlen(new_line-1)] = '\0';
                }
                if (line[i] != '\0'&& line[i] != '$'){
                    char str[2];
                    str[0] = line[i];
                    str[1] = '\0';
                    strcat(new_line, str);
                }
                else if (line[i] == '$'){
                    i --;
                }
                else {
                   return new_line;
                }
            }
            else {
                char str[3];
                str[0] = line[i-1];
                str[1] = line[i];
                str[2] = '\0';
                strcat(new_line, str);
            }
            free(variable);
        }
        else {
            char str[2];
            str[0] = line[i];
            str[1] = '\0';
            strcat(new_line, str);
        }
    }
    return new_line;
}
