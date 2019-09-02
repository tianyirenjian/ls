#ifndef _STRARRAY_H
#define _STRARRAY_H

typedef struct strArray {
    char** content;
    int length;
} strArray;

void *sortStrArrayContent(strArray* sa);
void removeElementByIndex(strArray* sa, int index);

#endif
