CC = gcc
CFLAGS = -std=c89 -Wall -fPIC
FLAGS = -Wall -g -o
LIB_NAME = libso_stdio.so
DEPLOY_PATH = ../test/checker-lin/
ROOT_PATH = ..
TEST_NUMBER = 41
TEST_SCRIPT = ./_test/run_test.sh
LOG = _log
SOURCE = os_io.c
OBJECT = os_io.o


build:	$(OBJECT)
	$(CC) -shared -o $(DEPLOY_PATH)$(LIB_NAME) $^
	cp $(SOURCE) $(DEPLOY_PATH)
	$(CC) -shared -o ../libos_io.so $^
$(OBJECT) : $(SOURCE)

run: build
	cd $(DEPLOY_PATH) &&\
	make -f Makefile.checker > ../../result.out 2>../../error.out

run_test: build
	cd $(DEPLOY_PATH) && \
	$(TEST_SCRIPT) init &&\
	$(TEST_SCRIPT) $(TEST_NUMBER) &&\
	$(TEST_SCRIPT) clean

.PHONY: clean save
save: clean
	cd $(ROOT_PATH) &&\
	git add -A	&&\
	echo Enter commit message: &&\
	read line &&\
	git commit -m "$$line" &&\
	git push

clean:
	rm -f *.o $(DEPLOY_PATH)$(LIB_NAME) *.out $(DEPLOY_PATH)$(LOG) $(DEPLOY_PATH)$(SOURCE)