CXX						:= g++
CXX_FLAGS			:= -std=c++17 -ggdb

DRIVER_PATH		:= Driver
BIN_PATH			:= bin
SRC_PATH			:= $(DRIVER_PATH)/src
INCLUDE_PATH	:= $(DRIVER_PATH)/src
CFG_FILENAME  := KleanerConfig.json

LIBRARIES			:= -lpthread
EXECUTABLE		:= Kleaner

all: bin_dir $(BIN_PATH)/$(EXECUTABLE)

run: all
	./$(BIN_PATH)/$(EXECUTABLE) ./$(BIN_PATH)/$(CFG_FILENAME) 

$(BIN_PATH)/$(EXECUTABLE): $(SRC_PATH)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE_PATH) $^ -o $@ $(LIBRARIES)
	cp $(DRIVER_PATH)/$(CFG_FILENAME) $(BIN_PATH)/$(CFG_FILENAME)

clean:
	-rm $(BIN_PATH)/*

bin_dir:
	mkdir -p $(BIN_PATH)
