OBJS = Main.o FileReader.o Token.o TokenHistogram.o Tokenizer.o
CC = g++
DEBUG = -g
C14FLAGS = -std=c++14
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

bin/Main : $(OBJS)
	$(CC) $(C14FLAGS) $(LFLAGS) $(OBJS) -o bin/Main

Main.o : src/Main.cpp src/Token.h src/Tokenizer.h src/TokenHistogram.h
	$(CC) $(C14FLAGS) $(CFLAGS) src/Main.cpp

FileReader.o : src/FileReader.cpp src/FileReader.h
	$(CC) $(C14FLAGS) $(CFLAGS) src/FileReader.cpp

Token.o : src/Token.cpp src/Token.h
	$(CC) $(C14FLAGS) $(CFLAGS) src/Token.cpp

TokenHistogram.o : src/TokenHistogram.cpp src/TokenHistogram.h src/Token.h
	$(CC) $(C14FLAGS) $(CFLAGS) src/TokenHistogram.cpp

Tokenizer.o : src/Tokenizer.cpp src/Tokenizer.h src/Token.h src/FileReader.h
	$(CC) $(C14FLAGS) $(CFLAGS) src/Tokenizer.cpp

clean:
	\rm *.o bin/Main