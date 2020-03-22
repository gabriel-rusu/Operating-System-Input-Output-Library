#include "utils.h"

SO_FILE *so_fopen(const char *pathname, const char *mode)
{
    SO_FILE *stream = NULL;
    create(&stream, mode);
    if (set(stream, mode) == SO_EOF)
    {
        delete (stream);
        return NULL;
    }
    stream->descriptor = open(pathname, stream->flags, stream->mode);
    if (stream->descriptor == SO_EOF)
    {
        delete (stream);
        return NULL;
    }
    else
        return stream;
}

void create(SO_FILE **stream, const char *mode)
{
    *stream = malloc(sizeof(SO_FILE));
    (*stream)->last_op = false;
    (*stream)->start = 0;
    (*stream)->end = 0;
    (*stream)->curr_pos = 0;
    (*stream)->buffer = malloc(sizeof(char) * BUFFER_SIZE);
}

int set(SO_FILE *stream, const char *mode)
{
    stream->mode = 0666;
    if (is("r", mode))
        stream->flags = O_RDONLY;
    else if (is("r+", mode))
        stream->flags = O_RDWR;
    else if (is("w", mode))
        stream->flags = O_WRONLY | O_CREAT | O_TRUNC;
    else if (is("w+", mode))
        stream->flags = O_RDWR | O_CREAT | O_TRUNC;
    else if (is("a", mode))
        stream->flags = O_WRONLY | O_CREAT | O_APPEND;
    else if (is("a+", mode))
        stream->flags = O_RDWR | O_CREAT | O_APPEND;
    else
        return SO_EOF;
    return SO_SET;
}

bool is(char *target, const char *mode)
{
    return strcmp(target, mode) == 0;
}

int so_fclose(SO_FILE *stream)
{
    if (stream->last_op == WRITE)
        so_fflush(stream);
    if (close(stream->descriptor))
    {
        delete (stream);
        return SO_EOF;
    }
    else
    {
        delete (stream);
        return 0;
    }
}

bool isFull(SO_FILE *stream)
{
    return stream->start == stream->end && stream->start != 0;
}

int so_fileno(SO_FILE *stream)
{
    return stream->descriptor;
}

int so_fflush(SO_FILE *stream) // TODO: de reverificat
{
    int count = stream->end - stream->start;
    char *buffer = stream->buffer + stream->start;
    int returnValue = write(stream->descriptor, buffer, count * sizeof(char));
    stream->start = stream->end = 0;
    if (returnValue < 0)
        return SO_EOF;
    else
        return 0;
}

void fill(SO_FILE *stream)
{
    int old_pos = lseek(stream->descriptor, 0, SEEK_CUR);
    int pos = lseek(stream->descriptor, 0, SEEK_END);
    lseek(stream->descriptor, old_pos, SEEK_SET);
    int bytes = (pos - old_pos) <= BUFFER_SIZE ? (pos - old_pos) : BUFFER_SIZE;
    stream->end = read(stream->descriptor, stream->buffer, bytes);
}

int so_fgetc(SO_FILE *stream)
{
    if (isEmpty(stream) || isFull(stream))
    {
        stream->end = stream->start = 0;
        fill(stream);
        if (stream->end == 0)
        {
            return SO_EOF;
        }
        else if (stream->end == SO_EOF)
        {
            return SO_EOF;
        }
        else
        {
            stream->last_op = READ;
            return stream->buffer[stream->start++];
        }
    }
    else
    {
        stream->last_op = READ;
        return stream->buffer[stream->start++];
    }
}

bool isNotFull(SO_FILE *stream)
{
    return !(stream->end == BUFFER_SIZE);
}

int so_fputc(int c, SO_FILE *stream)
{
    if (isNotFull(stream))
    {

        stream->last_op = WRITE;
        return stream->buffer[stream->end++] = (char)c;
    }
    else
    {
        so_fflush(stream);
        stream->last_op == WRITE;
        return stream->buffer[stream->end++] = (char)c;
    }
}

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
    for (int index = 0; index < nmemb * size; index += size)
    {
        for (int miniByte = 0; miniByte < size; miniByte++)
            *((char *)ptr + index + miniByte) = so_fgetc(stream);
    }
    stream->curr_pos+=nmemb*size;
    return nmemb;
}

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
    for (size_t index = 0; index < nmemb * size; index += size)
    {
        for (int byte = 0; byte < size; byte++)
            so_fputc(*((char *)ptr + byte + index), stream);
    }
    stream->curr_pos+=nmemb*size;
    return nmemb;
}

int so_fseek(SO_FILE *stream, long offset, int whence)
{

    stream->curr_pos = lseek(stream->descriptor, offset, whence);
    return stream->curr_pos == -1 ? SO_EOF : 0;
}

long so_ftell(SO_FILE *stream)
{
    // return lseek(stream->descriptor, 0, SEEK_CUR);
    return stream->curr_pos;
}

bool isEmpty(SO_FILE *stream)
{
    return stream->start == stream->end && stream->start == 0;
}

int so_feof(SO_FILE *stream)
{
    int currentPos = lseek(stream->descriptor, 0, SEEK_CUR);
    int fileEndPos = lseek(stream->descriptor, 0, SEEK_END);
    lseek(stream->descriptor, currentPos, SEEK_SET);
    return currentPos - fileEndPos;
}
int so_ferror(SO_FILE *stream)
{
    return 0;
}

SO_FILE *so_popen(const char *command, const char *type)
{
    return NULL;
}
int so_pclose(SO_FILE *stream)
{
    return SO_EOF;
}

void delete (SO_FILE *stream)
{
    free(stream->buffer);
    free(stream);
}