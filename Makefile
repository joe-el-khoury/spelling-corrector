OBJS = bin/Main.o bin/FileReader.o bin/Token.o bin/TokenHistogram.o \
	bin/Tokenizer.o bin/SpellingCorrector.o bin/TokenEditor.o bin/IteratorInterface.o \
	bin/MySQLInterface.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -O3 -std=c++14 -c -I/usr/include/cppconn $(DEBUG)
LFLAGS = -Wall -lmysqlcppconn $(DEBUG)

bin/Main : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o bin/Main

bin/Main.o : src/Main.cpp src/Token.h src/Tokenizer.h src/TokenHistogram.h src/util/FileReader.h src/SpellingCorrector.h
	$(CC) $(CFLAGS) src/Main.cpp -o bin/Main.o

bin/FileReader.o : src/util/FileReader.*
	$(CC) $(CFLAGS) src/util/FileReader.cpp -o bin/FileReader.o

bin/Token.o : src/Token.* src/TokenEditor.h
	$(CC) $(CFLAGS) src/Token.cpp -o bin/Token.o

bin/TokenHistogram.o : src/TokenHistogram.* src/Token.h
	$(CC) $(CFLAGS) src/TokenHistogram.cpp -o bin/TokenHistogram.o

bin/Tokenizer.o : src/Tokenizer.* src/Token.h src/util/FileReader.h
	$(CC) $(CFLAGS) src/Tokenizer.cpp -o bin/Tokenizer.o

bin/SpellingCorrector.o : src/SpellingCorrector.* src/Tokenizer.h src/TokenHistogram.h src/util/FileReader.h
	$(CC) $(CFLAGS) src/SpellingCorrector.cpp -o bin/SpellingCorrector.o

bin/TokenEditor.o : src/TokenEditor.* src/Token.h
	$(CC) $(CFLAGS) src/TokenEditor.cpp -o bin/TokenEditor.o

bin/IteratorInterface.o : src/util/IteratorInterface.*
	$(CC) $(CFLAGS) src/util/IteratorInterface.cpp -o bin/IteratorInterface.o

bin/MySQLInterface.o : src/util/MySQLInterface.*
	$(CC) $(CFLAGS) src/util/MySQLInterface.cpp -o bin/MySQLInterface.o

clean:
	rm -rf bin/*