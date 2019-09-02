#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "strarray.h"

typedef int bool;
#define true 1
#define false 0

#define MALLOC_STEP 50

char *getPath(int argv, char** args);
char *getOptions(int argv, char** args);
bool hasOption(char *options, char option);
strArray *listDir(char* path);

int main(int argv, char** args)
{
    char* path = ".";
    if (argv > 1) {
        path = getPath(argv, args);
    }
    char *options = getOptions(argv, args);
    bool all = hasOption(options, 'a');

    strArray *dirs = listDir(path);
    if (!all) {
        for (int k = 0; k < dirs->length; k++) {
            if (strlen(dirs->content[k]) == 0 || dirs->content[k][0] == '.') {
                removeElementByIndex(dirs, k);
                k--;
            }
        }
    }
    sortStrArrayContent(dirs);
    for (int i = 0; i < dirs->length; i ++) {
        printf("%s", dirs->content[i]);
        if (i != dirs->length - 1) {
            printf("\n");
        }
    }
    printf("\n");
}

char* getPath(int argv, char** args)
{
    for (int i = 1; i < argv; i++) {
        if (args[i][0] != '-') {
            return args[i];
        }
    }
    return ".";
}

char *getOptions(int argv, char** args)
{
    char* options = malloc(MALLOC_STEP * sizeof(char));
    int j = 0, k;
    for (int i = 1; i < argv;i ++) {
        if (args[i][0] == '-') {
            k = 1;
            while(args[i][k] != '\0') {
                options[j++] = args[i][k];
                if (j % MALLOC_STEP == 0) {
                    options = realloc(options, (j + MALLOC_STEP) * sizeof(char));
                }
                k++;
            }
        }
    }
    return options;
}

bool hasOption(char *options, char option)
{
    int i = 0;
    while (options[i] != '\0') {
        if (options[i] == option) {
            return true;
        }
        i++;
    }
    return false;
}

strArray *listDir(char* path)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(path);

    char **dirs = malloc(MALLOC_STEP * sizeof(char*));
    strArray *sa = malloc(sizeof(strArray));

    if (d) {
        int i = 0;
        while((dir = readdir(d)) != NULL) {
            dirs[i] = dir->d_name;
            if (++i % MALLOC_STEP == 0) {
                dirs = realloc(dirs, (i + MALLOC_STEP) * sizeof(char*));
            }
        }
        closedir(d);
        sa->content = dirs;
        sa->length = i;
    }
    return sa;
}
