CC=g++-4.8 -std=c++0x
TMP=temp
LIB=lib
BIN=bin
PROJECT_NAME=libHue
INCLUDE_DIRS=-I./../lib_hue -I./../JsonCpp/include -I./../libcurl_src/include
COMPILER_OPTIONS=-O -Wall -g
PREPROCESSOR=-DLINUX

$(PROJECT_NAME).a: $(TMP)/HttpClient.o $(TMP)/HueBridge.o $(TMP)/HueBridgeLocator.o $(TMP)/Settings.o $(TMP)/UrlProvider.o $(TMP)/HueSystemInformation.o
	ar ru $(LIB)/$@ $(TMP)/$^
	ranlib $(LIB)/$@
#	$(CC) -o $(BIN)/$(PROJECT_NAME) ./$(TMP)/HueBridge.o -I./../lib_hue

HttpClient.o: HttpClient.cpp
	$(CC) $(COMPILER_OPTIONS) $(PREPROCESSOR) -c HttpClient.cpp -o ./$(TMP)/HttpClient.o $(INCLUDE_DIRS)

HueBridge.o: HueBridge.cpp
	$(CC) $(COMPILER_OPTIONS) $(PREPROCESSOR) -c HueBridge.cpp -o ./$(TMP)/HueBridge.o $(INCLUDE_DIRS)

HueBridgeLocator.o: HueBridgeLocator.cpp
	$(CC) $(COMPILER_OPTIONS) $(PREPROCESSOR) -c HueBridgeLocator.cpp -o ./$(TMP)/HueBridgeLocator.o $(INCLUDE_DIRS)

Settings.o: Settings.cpp
	$(CC) $(COMPILER_OPTIONS) $(PREPROCESSOR) -c Settings.cpp -o ./$(TMP)/Settings.o $(INCLUDE_DIRS)

UrlProvider.o: UrlProvider.cpp
	$(CC) $(COMPILER_OPTIONS) $(PREPROCESSOR) -c UrlProvider.cpp -o ./$(TMP)/UrlProvider.o $(INCLUDE_DIRS)

#///////////
#ObjectModel
#///////////

HueSystemInformation.o: ObjectModel/HueSystemInformation.cpp
	$(CC) $(COMPILER_OPTIONS) $(PREPROCESSOR) -c ObjectModel/HueSystemInformation.cpp -o ./$(TMP)/HueSystemInformation.o $(INCLUDE_DIRS)

run:
	./main

install:


clean:
	@rm -f -r $(TMP)
	@rm -f -r $(BIN)
