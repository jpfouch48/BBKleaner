PROJECT=.\\Driver\\Kleaner
PROJECT_CFG=.\\Driver\\KleanerConfig.json

TARGET_IP=192.168.7.2
TARGET_DIR=kleaner
TARGET_USER=debian

# Two additional CFLAGS must be used for Angstrom
# They must not be used for Debian or Ubuntu. I couldn't find out why. 
# The hint came from C:\gcc-linaro\share\doc\gcc-linaro-arm-linux-gnueabihf\README.txt 
#
# Uncomment the following line if you use Angstrom on your BeagleBone
#TARGET=angstrom

# Directory for includes
CSOURCE = .\\Driver\\src
CINCLUDE = $(CSOURCE)

# Directory for Cpp-Source
vpath %.cpp $(CSOURCE)

# Directory for object files
OBJDIR = .\\Driver\\bin

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
 $(OBJDIR)/LogInstance.o \
 $(OBJDIR)/LogMgr.o 

# gcc binaries to use
CC = "C:\bin\gcc-linaro-7.5.0-2019\bin\arm-linux-gnueabihf-g++.exe"
LD = "C:\bin\gcc-linaro-7.5.0-2019\bin\arm-linux-gnueabihf-g++.exe"
SCP = "C:\bin\Putty\pscp.exe"

SHELL = cmd
REMOVE = del /F

# Compiler options
# Two additional flags neccessary for Angstrom Linux. Don't use them with Ubuntu or Debian  
CFLAGS = -marm
ifeq ($(TARGET),angstrom)
CFLAGS += -march=armv4t
CFLAGS += -mfloat-abi=soft
endif
CFLAGS += -O0 
CFLAGS += -g 
CFLAGS += -I.
CFLAGS += -lpthread
CFLAGS += -I$(CINCLUDE)
CFLAGS += $(CDEFINE)

# Our favourite
all: $(PROJECT)

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

