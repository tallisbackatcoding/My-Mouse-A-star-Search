#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static char left_over[READLINE_READ_SIZE];

int my_strlen(char *s)
{
    int i = 0;
    while(s[i]){
        i++;
    }
    return i;
}
void my_strcpy(char *s1, char *s2)
{
    int i;
    for(i = 0; s2[i]; i++){
        s1[i] = s2[i];
    }
    s1[i] = 0;
}
void my_strcat(char *s1, char *s2)
{
    int i = 0;
    while(s1[i])
        i++;
    int j = 0;
    while(s2[j]){
        s1[i] = s2[j];
        i++;
        j++;
    }
    s1[i] = s2[j];
}

void my_special_concat(char **to, char *from){
    int size1 = my_strlen(*to);
    int size2 = my_strlen(from);
    if(size2 == 0 || size1 == 0){
        return;
    }
    char temp[size1+1];
    my_strcpy(temp, *to);
    *to = (char *)realloc(*to, (size1 + size2 + 1));
    my_strcpy(*to, temp);
    int i;
    for(i = 0; from[i] != '\n' && from[i] != 0; i++){
        (*to)[size1+i] = from[i];
    }
    (*to)[size1 + i] = 0;
}

int find_new_line_index(char *str){
    for(int i = 0; str[i]; i++){
        if(str[i] == '\n'){
            return i;
        }
    }
    return -1;
}

char *my_readline(int fd){
    if(fd < 0){
        return NULL;
    }
    int length = -1;
    char *buffer = malloc((READLINE_READ_SIZE + 1) * sizeof(char));

    if(left_over[0] == 0){
        length = read(fd, buffer, READLINE_READ_SIZE);
        if(length == -1 || length == 0){
            free(buffer);
            return NULL;
        }
        buffer[length] = 0;
    }else{
        //if there is something in left_over I copy from it to buffer and then read
        my_strcpy(buffer, left_over);
        int rem_chars = READLINE_READ_SIZE - my_strlen(buffer);
        char remaining_chars[rem_chars];
        int end = read(fd, remaining_chars, rem_chars);
        remaining_chars[end] = 0;
        my_strcat(buffer, remaining_chars);
    }

    int new_line_index = find_new_line_index(buffer);

    if(new_line_index != -1)
        buffer[new_line_index] = 0;
    int i;


    //if new line was found we copy chars after new_line to left_over[] array
    if(new_line_index != -1){
        new_line_index++;
        for(i = 0; buffer[i + new_line_index]; i++){
            left_over[i] = buffer[i + new_line_index];
        }
        left_over[i] = 0;

    }else{
        //if it wasn't found we read from fd untill we find is new_line or end of file
        left_over[0] = 0;
        char temp[READLINE_READ_SIZE];
        while(1){
            int stop = read(fd, temp, READLINE_READ_SIZE);
            temp[stop] = 0;
            my_special_concat(&buffer, temp);
            new_line_index = find_new_line_index(temp);
            if(new_line_index != -1 || !stop){
                break;
            }
        }
        //and if it was found we copy to left_over again
        if(new_line_index -= -1){
            for(i = 0; temp[i + new_line_index]; i++){
                left_over[i] = temp[i+new_line_index];
            }
            left_over[i] = 0;
        }

    }
    return buffer;
}
