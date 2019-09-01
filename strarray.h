typedef struct strArray {
    char** content;
    int length;
} strArray;

void *sortStrArrayContent(strArray* sa);
