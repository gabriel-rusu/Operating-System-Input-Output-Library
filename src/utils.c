#include "utils.h"

SO_FILE *so_fopen(const char *pathname, const char *mode)
{
    SO_FILE *file_stream = NULL;
    create(&file_stream, mode);
    file_stream->descriptor = open(pathname, file_stream->flags, file_stream->mode);
    return file_stream;
}

void create(SO_FILE **file_stream, char *mode)
{
    *file_stream = malloc(sizeof(SO_FILE));
    set(file_stream, mode);
    (*file_stream)->buffer = malloc(sizeof(char) * BUFFER_SIZE);
}

int set(SO_FILE *file_stream, char *mode)
{
    file_stream->mode = 0666;
    if (is("r", mode))
        file_stream->flags = O_RDONLY;
    else if (is("r+", mode))
        file_stream->flags = O_RDWR;
    else if (is("w", mode))
        file_stream->flags = O_WRONLY | O_CREAT | O_TRUNC;
    else if (is("w+", mode))
        file_stream->flags = O_RDWR | O_CREAT | O_TRUNC;
    else if (is("a", mode))
        file_stream->flags = O_WRONLY | O_CREAT | O_APPEND;
    else if (is("a+", mode))
        file_stream->flags = O_RDWR | O_CREAT | O_APPEND;
}

bool is(char *target, char *mode)
{
    return strcmp(target, mode) == 0;
}