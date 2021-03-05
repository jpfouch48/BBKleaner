PROJECT=.\\bin\\kleaner
PROJECT_CFG=.\\Driver\\KleanerConfig.json

TARGET_IP=192.168.7.2
TARGET_DIR=kleaner
TARGET_USER=ubuntu

# Directory for includes
SOURCE = .\\Driver\\src
EXTERNAL = .\\Driver\\external
INCLUDES = -I. \
	-I$(SOURCE) \
	-I$(EXTERNAL)
	

# Directory for Cpp-Source
vpath %.cpp $(SOURCE)

# Directory for object files
OBJDIR = .\\Driver\\bin

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
CC = "C:\bin\gcc-linaro-7.5.0-2019\bin\arm-linux-gnueabihf-g++.exe"
LD = "C:\bin\gcc-linaro-7.5.0-2019\bin\arm-linux-gnueabihf-g++.exe"
SCP = "C:\bin\Putty\pscp.exe"

SHELL = cmd
REMOVE = del /F
MKDIR = mkdir

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
	$(SCP) $(PROJECT) $(PROJECT_CFG) $(TARGET_USER)@$(TARGET_IP):$(TARGET_DIR)

# Linker call
$(PROJECT): $(COBJ)
	$(LD) -o $@ $^ $(CFLAGS)

# Compiler call
$(COBJ): $(OBJDIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	$(REMOVE) $(PROJECT)
	$(REMOVE) $(OBJDIR)\\*.o

