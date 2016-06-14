build:
	g++ -g -std=c++14 -Wall \
	src/Main.cpp \
	src/Tokenizer.h src/Tokenizer.cpp \
	src/Token.h src/Token.cpp \
	src/FileReader.h src/FileReader.cpp \
	src/TokenHistogram.h src/TokenHistogram.cpp \
	-o bin/Main