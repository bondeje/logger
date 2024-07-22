CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -Wno-unused-parameter -Wno-unused-but-set-variable -fPIC
IFLAGS = -Iinclude
LFLAGS = 
BIN_DIR = bin
OBJ_DIR = obj

all: build_hierarchy src/logger.o

test: test_base.exe

build_hierarchy: $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR): ; @mkdir -p $@

$(BIN_DIR): ; @mkdir -p $@

src/logger.o: src/logger.c
	$(CC) $(CFLAGS) -c $(IFLAGS) src/logger.c -o obj/logger.o $(LFLAGS)

test_base.exe: src/logger.o
	del /f bin\test_base.log
	$(CC) $(CFLAGS) $(IFLAGS) test/test_base.c obj/logger.o -o bin/test_base.exe $(LFLAGS)
	$(CC) $(CFLAGS) -DMAX_LOGGING_LEVEL=LOG_LEVEL_WARN $(IFLAGS) test/test_base.c obj/logger.o -o bin/test_base_maxwarn.exe $(LFLAGS)
	$(CC) $(CFLAGS) -DDISABLE_LOGGING $(IFLAGS) test/test_base.c obj/logger.o -o bin/test_base_disabled.exe $(LFLAGS)
	echo "from bin/test_base.exe" >> bin/test_base.log
	bin/test_base.exe
	echo "from bin/test_base_maxwarn.exe" >> bin/test_base.log
	bin/test_base_maxwarn.exe
	echo "from bin/test_base_disabled.exe" >> bin/test_base.log
	bin/test_base_disabled.exe

clean:
	del /f /q bin\*.exe
	del /f /q bin\*.log
	del /f /q src\*.o