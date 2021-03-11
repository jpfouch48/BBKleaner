PROJECT     = ./bin/kleaner
PROJECT_CFG = ./cfg/*

DEPLOY_IP   = 192.168.7.2
DEPLOY_USER = debian

# Directory for includes
SRC_PATH = ./src
EXTERNAL = ./external


SRC_INC = -I. \
	-I$(SRC_PATH) \
	-I/usr/arm-linux-gnueabihf/include/c++/8 \
	-I$(EXTERNAL)

LIB_INC = 

# Directory for Cpp-Source
vpath %.cpp $(SRC_PATH)

# Directory for object files
OBJDIR = ./bin/obj

# Other dependencies
DEPS = \
 Makefile 

# Compiler object files 
COBJ = \
 $(OBJDIR)/Kleaner.o \
 $(OBJDIR)/CfgMgr.o \
 $(OBJDIR)/Device.o \
 $(OBJDIR)/DeviceType.o \
 $(OBJDIR)/Driver.o \
 $(OBJDIR)/GPIOConst.o \
 $(OBJDIR)/GPIOMgr.o \
 $(OBJDIR)/LogInstance.o \
 $(OBJDIR)/LogMgr.o 
 

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
all: $(OBJDIR) $(PROJECT)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

deploy: all
	$(SCP) $(PROJECT)     						$(DEPLOY_USER)@$(DEPLOY_IP):./bin
	$(SCP) $(PROJECT).sh  						$(DEPLOY_USER)@$(DEPLOY_IP):./bin
	$(SCP) $(PROJECT_CFG) 						$(DEPLOY_USER)@$(DEPLOY_IP):./cfg

# Linker call
$(PROJECT): $(COBJ)
	$(LD) -o $@ $^ $(LFLAGS)

# Compiler call
$(COBJ): $(OBJDIR)/%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

clean:
	$(REMOVE) $(PROJECT)
	$(REMOVE) $(OBJDIR)

