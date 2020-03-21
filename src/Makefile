CC = gcc
CFLAGS = -Wall -fPIC
FLAGS = -Wall -g -o
LIB_NAME = libso_stdio.so
DEPLOY_PATH = ../test/checker-lin/
TESTS = _test
TEST_NUMBER = 1
TEST_SCRIPT = ./_test/run_test.sh


build:	utils.o
	$(CC) -shared -o $(DEPLOY_PATH)$(LIB_NAME) $^
utils.o : utils.c

run: build
	cd $(DEPLOY_PATH);make -f Makefile.checker

run_test: build
	cd $(DEPLOY_PATH)$(TESTS) && cd .. && $(TEST_SCRIPT) init &&\
	$(TEST_SCRIPT) $(TEST_NUMBER) &&\
	$(TEST_SCRIPT) clean

.PHONY: clean
clean:
	rm -f *.o $(DEPLOY_PATH)$(LIB_NAME)