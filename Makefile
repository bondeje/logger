.POSIX:
# to prevent funny business with FreeBSD's make
.OBJDIR: .
.SUFFIXES:
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -Wno-unused-parameter -Wno-unused-but-set-variable -fPIC
BLDCFLAGS = $(CFLAGS) -O2 -DNDEBUG
#DBGCFLAGS = $(CFLAGS) -g3 -O0 -fsanitize=address,undefined
DBGCFLAGS = $(CFLAGS) -g3 -O0
IFLAGS = -Iinclude
DBGLFLAGS =
LFLAGS = 

LIB_OBJS = src/logger.o
DBG_LIB_OBJS = src/logger.do

all: test

.MAIN: all

build_paths:
	@mkdir -p bin

test: build_paths $(LIB_OBJS) $(DBG_LIB_OBJS) bin/test_base bin/test_base_maxwarn bin/test_base_disabled
	@echo "from test_base" > bin/test_base.log
	bin/test_base > test_base.log 2>test_base_err.log
	@echo " "
	@echo "from test_base_maxwarn" >> bin/test_base.log
	bin/test_base_maxwarn > test_base_maxwarn.log 2>test_base_maxwarn_err.log
	@echo " "
	@echo "from bin/test_base_disabled.exe" >> bin/test_base.log
	bin/test_base_disabled > test_base_disabled.log 2>test_base_disabled_err.log

bin/test_base: $(DBG_LIB_OBJS) test/test_base.c
	@if [ -n "$(SANITIZE)" ] ; then export DBGOPT="-fsanitize=address,undefined"; else export DBGOPT="" ; fi ; \
	$(CC) $(DBGCFLAGS) $$DBGOPT -DMAX_LOGGING_LEVEL=LOG_LEVEL_TRACE $(IFLAGS) test/test_base.c $(DBG_LIB_OBJS) -o bin/test_base

bin/test_base_maxwarn: $(DBG_LIB_OBJS) test/test_base.c
	@if [ -n "$(SANITIZE)" ] ; then export DBGOPT="-fsanitize=address,undefined"; else export DBGOPT="" ; fi ; \
	$(CC) $(DBGCFLAGS) $$DBGOPT -DMAX_LOGGING_LEVEL=LOG_LEVEL_WARN $(IFLAGS) test/test_base.c $(DBG_LIB_OBJS) -o bin/test_base_maxwarn

bin/test_base_disabled: $(DBG_LIB_OBJS) test/test_base.c
	@if [ -n "$(SANITIZE)" ] ; then export DBGOPT="-fsanitize=address,undefined"; else export DBGOPT="" ; fi ; \
	$(CC) $(DBGCFLAGS) $$DBGOPT -DDISABLE_LOGGING $(IFLAGS) test/test_base.c  $(DBG_LIB_OBJS) -o bin/test_base_disabled
	
clean:
	@rm -f test_base test_base_maxwarn test_base_disabled src/*.o src/*.do *.log
	@rm -rf bin

.SUFFIXES: .c .o .do
.c.o:
	@$(CC) $(BLDCFLAGS) -c $(IFLAGS) $< -o $@

.c.do:
	@$(CC) $(DBGCFLAGS) -c $(IFLAGS) $< -o $@