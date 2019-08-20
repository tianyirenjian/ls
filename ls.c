#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#define MALLOC_STEP 50

typedef struct lstr {
    char** content;
    int length;
} lstr;

lstr *listdir(char* path);

int main(int argv, char* args[])
{
    char* path = ".";
    if (argv > 1) {
        path = args[1];
    }
    lstr *ls = listdir(path);
    for (int i = 0; i < ls->length; i ++) {
        printf("%s\n", ls->content[i]);
    }
}

lstr *listdir(char* path)
{
    DIR *d;
    struct dirent *dir;
    d = opendir(path);

    char **dirs = malloc(MALLOC_STEP * sizeof(char*));
    lstr *ls = malloc(sizeof(lstr));

    if (d) {
        int i = 0;
        while((dir = readdir(d)) != NULL) {
            dirs[i] = dir->d_name;
            if (++i % MALLOC_STEP == 0) {
                dirs = realloc(dirs, (i + MALLOC_STEP) * sizeof(char*));
            }
        }
        closedir(d);
        ls->content = dirs;
        ls->length = i;
    }
    return ls;
}
