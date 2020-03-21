CC = gcc
CFLAGS = -Wall -fPIC
FLAGS = -Wall -g -o
LIB_NAME = libso_stdio.so
DEPLOY_PATH = ../test/checker-lin/


build:	utils.o
	$(CC) -shared -o $(DEPLOY_PATH)$(LIB_NAME) $^
utils.o : utils.c

run: build
	cd $(DEPLOY_PATH);make -f Makefile.checker

.PHONY: clean
clean:
	rm -f *.o $(DEPLOY_PATH)$(LIB_NAME)