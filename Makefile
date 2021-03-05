PROJECT=./bin/kleaner
PROJECT_CFG=./cfg/KleanerConfig.json
PROJECT_SVR=./server/*

TARGET_IP=192.168.7.2
TARGET_USER=ubuntu
TARGET_DIR=.
TARGET_DIR_BIN=$(TARGET_DIR)/bin
TARGET_DIR_CFG=$(TARGET_DIR)/cfg
TARGET_DIR_SVR=$(TARGET_DIR)/server

# Directory for includes
SOURCE = ./Driver/src
EXTERNAL = ./Driver/external
INCLUDES = -I. \
	-I$(SOURCE) \
	-I$(EXTERNAL)
	

# Directory for Cpp-Source
vpath %.cpp $(SOURCE)

# Directory for object files
OBJDIR = ./Driver/obj

# Other dependencies
DEPS = \
 Makefile 

# Compiler object files 
COBJ = \
 $(OBJDIR)/Kleaner.o \
 $(OBJDIR)/CfgMgr.o \
 $(OBJDIR)/CommMgr.o \
 $(OBJDIR)/Device.o \
 $(OBJDIR)/DeviceType.o \
 $(OBJDIR)/Driver.o \
 $(OBJDIR)/LogInstance.o \
 $(OBJDIR)/LogMgr.o 
 

# gcc binaries to use
ifeq ($(OS),Windows_NT)
	CC = "C:\bin\gcc-linaro-7.5.0-2019\bin\arm-linux-gnueabihf-g++.exe"
	LD = "C:\bin\gcc-linaro-7.5.0-2019\bin\arm-linux-gnueabihf-g++.exe"
	SCP = "C:\bin\Putty\pscp.exe"
	REMOVE = del /F
	MKDIR = mkdir
else
	CC = arm-linux-gnueabihf-g++
	LD = arm-linux-gnueabihf-g++
	SCP = scp
	REMOVE = rm -rf
	MKDIR = mkdir
endif



# Compiler options
# Two additional flags neccessary for Angstrom Linux. Don't use them with Ubuntu or Debian  
CFLAGS = -marm
ifeq ($(TARGET),angstrom)
CFLAGS += -march=armv4t
CFLAGS += -mfloat-abi=soft
endif
CFLAGS += -Wno-psabi
CFLAGS += -O0 
CFLAGS += -g 
CFLAGS += -lpthread
CFLAGS += $(INCLUDES)

# Our favourite
all: $(OBJDIR) $(PROJECT)

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

deploy: all
	$(SCP) $(PROJECT) $(TARGET_USER)@$(TARGET_IP):$(TARGET_DIR_BIN)
	$(SCP) $(PROJECT).sh $(TARGET_USER)@$(TARGET_IP):$(TARGET_DIR)
	$(SCP) $(PROJECT_CFG) $(TARGET_USER)@$(TARGET_IP):$(TARGET_DIR_CFG)
	$(SCP) $(PROJECT_SVR) $(TARGET_USER)@$(TARGET_IP):$(TARGET_DIR_SVR)

# Linker call
$(PROJECT): $(COBJ)
	$(LD) -o $@ $^ $(CFLAGS)

# Compiler call
$(COBJ): $(OBJDIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	$(REMOVE) '$(PROJECT)'
	$(REMOVE) '$(OBJDIR)'

