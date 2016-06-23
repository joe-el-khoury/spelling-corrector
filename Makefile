OBJS = bin/Main.o bin/FileReader.o bin/Token.o bin/TokenHistogram.o bin/Tokenizer.o bin/SpellingCorrector.o
CC = g++
DEBUG = -g
EXTRAFLAGS = -std=c++14
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

bin/Main : $(OBJS)
	$(CC) $(EXTRAFLAGS) $(LFLAGS) $(OBJS) -o bin/Main

bin/Main.o : src/Main.cpp src/Token.h src/Tokenizer.h src/TokenHistogram.h src/FileReader.h src/SpellingCorrector.h
	$(CC) $(EXTRAFLAGS) $(CFLAGS) src/Main.cpp -o bin/Main.o

bin/FileReader.o : src/FileReader.cpp src/FileReader.h
	$(CC) $(EXTRAFLAGS) $(CFLAGS) src/FileReader.cpp -o bin/FileReader.o

bin/Token.o : src/Token.cpp src/Token.h
	$(CC) $(EXTRAFLAGS) $(CFLAGS) src/Token.cpp -o bin/Token.o

bin/TokenHistogram.o : src/TokenHistogram.cpp src/TokenHistogram.h src/Token.h
	$(CC) $(EXTRAFLAGS) $(CFLAGS) src/TokenHistogram.cpp -o bin/TokenHistogram.o

bin/Tokenizer.o : src/Tokenizer.cpp src/Tokenizer.h src/Token.h src/FileReader.h
	$(CC) $(EXTRAFLAGS) $(CFLAGS) src/Tokenizer.cpp -o bin/Tokenizer.o

bin/SpellingCorrector.o : src/SpellingCorrector.cpp src/SpellingCorrector.h src/Tokenizer.h src/TokenHistogram.h src/FileReader.h
	$(CC) $(EXTRAFLAGS) $(CFLAGS) src/SpellingCorrector.cpp -o bin/SpellingCorrector.o

bin/TokenEditor.o : src/TokenEditor.cpp src/TokenEditor.h src/Token.h
	$(CC) $(EXTRAFLAGS) $(CFLAGS) src/TokenEditor.cpp -o bin/TokenEditor.o

clean:
	\rm bin/*.o bin/Main