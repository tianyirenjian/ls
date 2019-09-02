#include <string.h>
#include <stdlib.h>
#include "strarray.h"

void *sortStrArrayContent(strArray* sa)
{
    for (int i = 0; i < sa->length; i ++) {
        for (int j = i + 1; j < sa->length; j++) {
            if (strcmp(sa->content[i], sa->content[j]) > 0) {
                char *temp = sa->content[i];
                sa->content[i] = sa->content[j];
                sa->content[j] = temp;
            }
        }
    }
}

void removeElementByIndex(strArray* sa, int index)
{
    for (int i = index; i < sa->length - 1; i ++) {
        sa->content[i] = sa->content[i + 1];
    }
    //free(sa->content[sa->length - 1]);
    sa->length --;
}
