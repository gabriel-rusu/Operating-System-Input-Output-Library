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
    (*stream)->last_op = NOT_SET;
    (*stream)->start = 0;
    (*stream)->end = 0;
    (*stream)->curr_pos = 0;
    (*stream)->eof = false;
    (*stream)->pid = -1;
    (*stream)->buffer = malloc(sizeof(char) * BUFFER_SIZE);
    (*stream)->error = false;
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

bool is(const char *target, const char *mode)
{
    return strcmp(target, mode) == 0;
}

int so_fclose(SO_FILE *stream)
{
    int flush_status = false;
    if (stream->last_op == WRITE)
        flush_status = so_fflush(stream);
    if (close(stream->descriptor) || flush_status)
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

int so_fflush(SO_FILE *stream)
{
    int count = stream->end - stream->start;
    char *buffer = stream->buffer + stream->start;
    int returnValue = write(stream->descriptor, buffer, count * sizeof(char));
    stream->start = stream->end = 0;
    if (returnValue < 0)
    {
        stream->error = true;
        return SO_EOF;
    }
    else
    {
        if (returnValue != count)
            stream->error = true;
        return 0;
    }
}

void fill(SO_FILE *stream)
{
    int old_pos = lseek(stream->descriptor, 0, SEEK_CUR);
    int pos = lseek(stream->descriptor, 0, SEEK_END);
    lseek(stream->descriptor, old_pos, SEEK_SET);
    int bytes = (pos - old_pos) <= BUFFER_SIZE ? (pos - old_pos) : BUFFER_SIZE;
    int bytesRead = read(stream->descriptor, stream->buffer, bytes);
    stream->end = (bytesRead == 0) ? SO_EOF : bytesRead;
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
            stream->eof = true;
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
        stream->last_op = WRITE;
        return stream->buffer[stream->end++] = (char)c;
    }
}

size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
    int members_read = 0;
    for (int index = 0; index < nmemb * size; index += size)
    {
        for (int miniByte = 0; miniByte < size; miniByte++)
        {
            if (stream->end != SO_EOF)
                *((char *)ptr + index + miniByte) = so_fgetc(stream);
            else
            {
                stream->eof = true;
                stream->error = true;
                return --members_read;
            }
        }
        members_read++;
    }
    stream->curr_pos += nmemb * size;
    return members_read;
}

size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
    int members_written = 0;
    for (size_t index = 0; index < nmemb * size; index += size)
    {
        for (int byte = 0; byte < size; byte++)
            so_fputc(*((char *)ptr + byte + index), stream);
        members_written++;
    }
    stream->curr_pos += members_written * size;
    return members_written;
}

int so_fseek(SO_FILE *stream, long offset, int whence)
{
    if (stream->last_op == WRITE)
    {
        so_fflush(stream);
    }
    else if (stream->last_op == READ)
    {
        stream->start = stream->end = 0;
    }

    stream->curr_pos = lseek(stream->descriptor, offset, whence);
    return stream->curr_pos == -1 ? SO_EOF : 0;
}

long so_ftell(SO_FILE *stream)
{
    return stream->curr_pos;
}

bool isEmpty(SO_FILE *stream)
{
    return stream->start == stream->end && stream->start == 0;
}

int so_feof(SO_FILE *stream)
{
    return stream->eof ? SO_EOF : 0;
}

void delete (SO_FILE *stream)
{
    free(stream->buffer);
    free(stream);
}

int so_ferror(SO_FILE *stream)
{
    return stream->error;
}

SO_FILE *so_popen(const char *command, const char *type)
{
    SO_FILE *stream = NULL;
    int pipe_descriptor[2];
    int pid;
    struct pid *volatile current;

    if (!(is(type, "r")) || !(is(type, "w")))
    {
        return NULL;
    }

    if ((current = malloc(sizeof(struct pid))) == NULL)
        return (NULL);
    if (pipe(pipe_descriptor) < 0)
    {
        free(current);
        return (NULL);
    }
    switch (pid = fork())
    {
    case -1: /* Error. */
        (void)close(pipe_descriptor[0]);
        (void)close(pipe_descriptor[1]);
        free(current);
        return (NULL);
        /* NOTREACHED */
    case 0: /* Child. */
    {

        /*
		 * We fork()'d, we got our own copy of the list, no
		 * contention.
		 */
        for (Node *current = pids; current; current = current->next)
            close(so_fileno(current->fp));
        if (is(type, "r"))
        {
            (void)close(pipe_descriptor[0]);
            if (pipe_descriptor[1] != STDOUT_FILENO)
            {
                (void)dup2(pipe_descriptor[1], STDOUT_FILENO);
                (void)close(pipe_descriptor[1]);
            }
        }
        else
        {
            (void)close(pipe_descriptor[1]);
            if (pipe_descriptor[0] != STDIN_FILENO)
            {
                (void)dup2(pipe_descriptor[0], STDIN_FILENO);
                (void)close(pipe_descriptor[0]);
            }
        }
        execlp("/bin/sh", "sh", "-c", command, (char *)NULL);
        _exit(127);
        /* NOTREACHED */
    }
    }
    if (is(type, "r"))
    {
        create(&(stream), type);
        stream->descriptor = pipe_descriptor[0];
        close(pipe_descriptor[1]);
    }
    else
    {
        create(&(stream), type);
        stream->descriptor = pipe_descriptor[1];
        close(pipe_descriptor[0]);
    }
    /* Link into list of file descriptors. */
    current->fp = stream;
    current->pid = pid;
    current->next = pids;
    pids = current;
    return stream;
}

int so_pclose(SO_FILE *stream)
{
    Node *cur, *last;
    int pstat;
    int pid;
    /* Find the appropriate file pointer. */
    for (last = NULL, cur = pids; cur; last = cur, cur = cur->next)
        if (cur->fp == stream)
            break;
    if (cur == NULL)
        return (-1);
    so_fclose(stream);
    do
    {
        pid = waitpid(cur->pid, &pstat, 0);
    } while (pid == -1 && errno == EINTR);
    /* Remove the entry from the linked list. */
    if (last == NULL)
        pids = cur->next;
    else
        last->next = cur->next;
    free(cur);
    return (pid == -1 ? -1 : pstat);
}

int setDescriptors(int descriptors[2], SO_FILE *stream, const char *type)
{
    switch (type[0])
    {
    case 'r':
        stream->descriptor = descriptors[0];
        return 1;
    case 'w':
        stream->descriptor = descriptors[1];
        return 0;
    }
}