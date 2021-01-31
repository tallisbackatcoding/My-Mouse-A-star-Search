#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../headers/functions.h"

int my_atoi(char* str){

    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i++;
    }

    for (; str[i] != '\0'; ++i){
        if(str[i] == 13 || str[i] == 10){
            break;
        }
        result = result * 10 + str[i] - '0';
    }

    return sign * result;
}

int my_strlen(char *s){
    int i = 0;
    while(s[i] != '\0'){
        i++;
    }
    return i;
}

void my_strcpy(char *s1, char *s2){
    int i;
    for(i = 0; s2[i]; i++){
        s1[i] = s2[i];
    }
    s1[i] = '\0';
}

void my_strcat(char *s1, char *s2){
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

int find_new_line_index(char *str){
    for(int i = 0; str[i]; i++){
        if(str[i] == '\n'){
            return i;
        }
    }
    return -1;
}

void line_by_line(char *str){
    for(int i = 0; str[i] != 0; i++){
        printf("%d th: :%c: or :%d:\n", i, str[i], str[i]);
    }
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

char *readWithSize(int fd, int readSize){
    if(fd == -1){
        return NULL;
    }
    char *buffer = malloc(sizeof(char)*(readSize+2));

    int strSize = read(fd, buffer, readSize+1);
    if(strSize != 0){
        buffer[readSize] = 0;
        //line_by_line(buffer);
        return buffer;
    }
    free(buffer);
    return NULL;
}

static char left_over[1000];

char *my_readline(int fd){

    if(fd < 0){
        return NULL;
    }
    int length = -1;
    char *buffer = malloc((1000 + 1) * sizeof(char));

    if(left_over[0] == 0){
        length = read(fd, buffer, 1000);
        if(length == -1 || length == 0){
            free(buffer);
            return NULL;
        }
        buffer[length] = 0;
    }else{
        //if there is something in left_over I copy from it to buffer and then read
        my_strcpy(buffer, left_over);
        int rem_chars = 1000 - my_strlen(buffer);
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
        char temp[1000];
        while(1){
            int stop = read(fd, temp, 1000);
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


