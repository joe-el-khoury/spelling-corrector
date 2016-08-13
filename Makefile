OBJS = bin/Main.o bin/FileReader.o bin/Token.o bin/TokenHistogram.o \
	bin/Tokenizer.o bin/SpellingCorrector.o bin/TokenEditor.o bin/IteratorInterface.o \
	bin/MySQLInterface.o bin/DatabaseConfigReader.o bin/SpellingCorrectorTrainer.o \
	bin/Ngram.o
CC = g++
DEBUG = -g
CFLAGS = -c -Wall -std=c++14 -I/usr/include/cppconn $(DEBUG)
LFLAGS = -lmysqlcppconn -lcrypto -lboost_program_options -lboost_iostreams $(DEBUG)

.PHONY: directories

all: directories bin/SpellingCorrector

directories: bin

bin:
	mkdir bin

bin/SpellingCorrector : $(OBJS)
	$(CC) -o bin/SpellingCorrector $(OBJS) $(LFLAGS)

bin/Main.o : src/Main.cpp src/SpellingCorrector.h src/SpellingCorrectorTrainer.h
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

bin/SpellingCorrectorTrainer.o : src/SpellingCorrectorTrainer.* src/util/FileReader.h src/Tokenizer.h src/util/MySQLInterface.h src/Token.h src/util/MD5FileHasher.h src/Ngram.h
	$(CC) $(CFLAGS) src/SpellingCorrectorTrainer.cpp -o bin/SpellingCorrectorTrainer.o

bin/TokenEditor.o : src/TokenEditor.* src/Token.h src/util/Helper.h
	$(CC) $(CFLAGS) src/TokenEditor.cpp -o bin/TokenEditor.o

bin/IteratorInterface.o : src/util/IteratorInterface.*
	$(CC) $(CFLAGS) src/util/IteratorInterface.cpp -o bin/IteratorInterface.o

bin/MySQLInterface.o : src/util/MySQLInterface.*
	$(CC) $(CFLAGS) src/util/MySQLInterface.cpp -o bin/MySQLInterface.o

bin/DatabaseConfigReader.o : config/DatabaseConfigReader.* src/util/MySQLInterface.h
	$(CC) $(CFLAGS) config/DatabaseConfigReader.cpp -o bin/DatabaseConfigReader.o

bin/Ngram.o : src/Ngram.* src/Token.h
	$(CC) $(CFLAGS) src/Ngram.cpp -o bin/Ngram.o

clean:
	rm -rf bin/*
