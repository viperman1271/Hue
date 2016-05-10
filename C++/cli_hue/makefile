CC=g++-4.8 -std=c++0x
TMP=temp
BIN=bin
PROJECT_NAME=hue
INCLUDE_DIRS=-I./../lib_hue -I./../JsonCpp/include -I./../libcurl_src/include
COMPILER_OPTIONS=-O -Wall -g

$(PROJECT_NAME): main.o
	$(CC) -o $(BIN)/$(PROJECT_NAME) ./$(TMP)/main.o ../lib_hue/lib/libHue.a ../JsonCpp/build/release/libjsoncpp.a ../libcurl_src/lib/libcurl.a -lz -lrt

main.o: main.cpp
	$(CC) $(COMPILER_OPTIONS) -c main.cpp -o ./$(TMP)/main.o $(INCLUDE_DIRS)

run:
	./main

install:


clean:
	@rm -f -r $(TMP)
	@rm -f -r $(BIN)
