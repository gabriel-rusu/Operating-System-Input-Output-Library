#include "../test/util/so_stdio.h"
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct SO_FILE
{
    int descriptor;
    char *buffer;
    int mode;
    int flags;
} SO_FILE;

#define BUFFER_SIZE 4096

void create(SO_FILE **file_stream, char *pathname, char *mode);