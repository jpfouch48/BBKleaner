CXX						:= g++
CXX_FLAGS			:= -std=c++17 -ggdb

BIN						:= bin
SRC						:= src
INCLUDE				:= src
CFG_FILE      := KleanerConfig.json

LIBRARIES			:= -lpthread
EXECUTABLE		:= Kleaner

all: $(BIN)/$(EXECUTABLE)

run: all
	./$(BIN)/$(EXECUTABLE) ./$(BIN)/$(CFG_FILE) 

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)
	cp $(CFG_FILE) $(BIN)/$(CFG_FILE)

clean:
	-rm $(BIN)/*
