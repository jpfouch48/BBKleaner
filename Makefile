PROJECT     = ./bin/kleaner
PROJECT_CFG = ./cfg/*

DEPLOY_IP   = 192.168.7.2
DEPLOY_USER = debian

# Directory for includes
SRC_PATH = ./src
OBJ_PATH = ./bin/obj
EXT_PATH = ./external


SRC_INC = -I. \
	-I$(SRC_PATH) \
	-I/usr/arm-linux-gnueabihf/include/c++/8 \
	-I$(EXT_PATH)

LIB_INC = 

# Directory for Cpp-Source
vpath %.cpp $(SRC_PATH)

SRC_FILES = $(shell find $(SRC_PATH) -type f -name *.cpp)
OBJ_FILES = $(patsubst $(SRC_PATH)%.cpp,$(OBJ_PATH)%.o,$(SRC_FILES))

# Other dependencies
DEPS = Makefile

# gcc binaries to use
CC     = arm-linux-gnueabihf-g++-8
LD     = $(CC)
SCP    = scp
REMOVE = rm -rf
MKDIR  = mkdir -p

# Compiler options
CFLAGS = -marm -Wno-psabi -O0 -g -std=c++17
CFLAGS += $(SRC_INC)

# Linker options
LFLAGS =  -lpthread -lstdc++fs
LFLAGS += $(LIB_INC)

# Our favourite
all: $(OBJ_PATH) $(PROJECT)

$(OBJ_PATH):
	$(MKDIR) $(OBJ_PATH)

deploy: all
	$(SCP) $(PROJECT)     						$(DEPLOY_USER)@$(DEPLOY_IP):./bin
	$(SCP) $(PROJECT).sh  						$(DEPLOY_USER)@$(DEPLOY_IP):./bin
	$(SCP) $(PROJECT_CFG) 						$(DEPLOY_USER)@$(DEPLOY_IP):./cfg

# Linker call
$(PROJECT): $(OBJ_FILES)
	$(LD) -o $@ $^ $(LFLAGS)

# Compiler call
$(OBJ_FILES): $(OBJ_PATH)/%.o: %.cpp $(DEPS) $(SRC_PATH)/%.h
	$(CC) $(CFLAGS) -c -o $@ $< 

clean:
	$(REMOVE) $(PROJECT)
	$(REMOVE) $(OBJ_PATH)

