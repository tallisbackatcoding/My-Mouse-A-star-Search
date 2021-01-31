#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#define READLINE_READ_SIZE 512



int my_atoi(char* str);
int my_strlen(char *s);
void my_strcpy(char *s1, char *s2);
void my_strcat(char *s1, char *s2);
void my_special_concat(char **to, char *from);
int find_new_line_index(char *str);
void line_by_line(char *str);
char * my_strtok( char *string, const char delim );
int priority(char op);
int is_number(char c);
int is_operator(char c);
float my_evaluate_expression(float a, float b, char op);
char *readWithSize(int fd, int readSize);
char *my_readline(int fd);


#endif
