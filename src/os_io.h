#include "../test/util/so_stdio.h"
#include <stdbool.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/param.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

typedef struct _so_file
{
    int descriptor;
    char *buffer;
    int start;
    int end;
    int mode;
    int flags;
    int curr_pos;
    int last_op;
    bool error;
    bool eof;
    int pid;
} SO_FILE;

typedef struct pid {
	struct pid *next;
	SO_FILE *fp;
	int pid;
} Node;
static Node *pids;


#define WRITE 2
#define READ 1
#define NOT_SET 0
#define SO_SET 1
#define BUFFER_SIZE 4096

SO_FILE *so_fopen(const char *pathname, const char *mode);
void create(SO_FILE **stream,const char *mode);
int set(SO_FILE *stream,const char *mode);
bool is(const char *target,const char *mode);
int so_fclose(SO_FILE *stream);
int so_fileno(SO_FILE *stream);
int so_fflush(SO_FILE *stream);
void delete(SO_FILE *stream);
void fill(SO_FILE *stream);
int so_fgetc(SO_FILE *stream);
bool isNotFull(SO_FILE *stream);
int so_fputc(int c, SO_FILE *stream);
size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream);
size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream);
int so_fseek(SO_FILE *stream, long offset, int whence);
long so_ftell(SO_FILE *stream);
bool isEmpty(SO_FILE *stream);
ssize_t xread(int fd, void *buf, size_t count);