OBJS = bin/Main.o bin/FileReader.o bin/Token.o bin/TokenHistogram.o bin/Tokenizer.o
CC = g++
DEBUG = -g
C14FLAGS = -std=c++14
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

bin/Main : $(OBJS)
	$(CC) $(C14FLAGS) $(LFLAGS) $(OBJS) -o bin/Main

bin/Main.o : src/Main.cpp src/Token.h src/Tokenizer.h src/TokenHistogram.h
	$(CC) $(C14FLAGS) $(CFLAGS) src/Main.cpp -o bin/Main.o

bin/FileReader.o : src/FileReader.cpp src/FileReader.h
	$(CC) $(C14FLAGS) $(CFLAGS) src/FileReader.cpp -o bin/FileReader.o

bin/Token.o : src/Token.cpp src/Token.h
	$(CC) $(C14FLAGS) $(CFLAGS) src/Token.cpp -o bin/Token.o

bin/TokenHistogram.o : src/TokenHistogram.cpp src/TokenHistogram.h src/Token.h
	$(CC) $(C14FLAGS) $(CFLAGS) src/TokenHistogram.cpp -o bin/TokenHistogram.o

bin/Tokenizer.o : src/Tokenizer.cpp src/Tokenizer.h src/Token.h src/FileReader.h
	$(CC) $(C14FLAGS) $(CFLAGS) src/Tokenizer.cpp -o bin/Tokenizer.o

clean:
	\rm bin/*.o bin/Main