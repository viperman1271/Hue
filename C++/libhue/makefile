# Declaration of variables
CC=g++-4.8 -std=c++0x
TMP=temp
LIB=lib
BIN=bin
CC_FLAGS=-w -O -Wall -g
PREPROCESSOR=-DLINUX -DVERBOSE_OUTPUT
INCLUDE_DIRS=-I./../lib_hue -I./../JsonCpp/include -I./../libcurl_src/include
PROJECT_NAME=libHue

# File names
EXEC=$(PROJECT_NAME).a
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
SOURCES_OM=$(wildcard ObjectModel/*.cpp)
OBJECTS_OM=$(SOURCES_OM:.cpp=.o)

# Main target
$(EXEC): $(OBJECTS) $(OBJECTS_OM)
	ar ru $(LIB)/$@ $^
	ranlib $(LIB)/$@

# To obtain object files
%.o: %.cpp
	$(CC) $(PREPROCESSOR) $(INCLUDE_DIRS) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
