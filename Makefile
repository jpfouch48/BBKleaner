PROJECT     = ./bin/kleaner
PROJECT_CFG = ./cfg/*

DEPLOY_IP   = 192.168.7.2
DEPLOY_USER = ubuntu
TARGET_FS   = /home/jfaucher/mnt_pbb

# Directory for includes
SRC_PATH = ./src
EXTERNAL = ./external


SRC_INC = -I. \
	-I$(SRC_PATH) \
	-I$(TARGET_FS)/usr/local/include \
	-I$(EXTERNAL)

LIB_INC = \
	-L$(TARGET_FS)/usr/lib/arm-linux-gnueabihf \
	-L$(TARGET_FS)/usr/local/lib

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
 $(OBJDIR)/CommMgr.o \
 $(OBJDIR)/Device.o \
 $(OBJDIR)/DeviceType.o \
 $(OBJDIR)/Driver.o \
 $(OBJDIR)/LogInstance.o \
 $(OBJDIR)/LogMgr.o 
 

# gcc binaries to use
CC     = arm-linux-gnueabihf-g++
LD     = $(CC)
SCP    = scp
SSHFS  = sshfs
REMOVE = rm -rf
MKDIR  = mkdir -p
UMOUNT = umount

# Compiler options
CFLAGS = -marm -Wno-psabi -O0 -g 
CFLAGS += $(SRC_INC)

# Linker options
LFLAGS =  -lpthread -lcppcms -lbooster -lz -lpcre -licuuc -licui18n -licudata
LFLAGS += $(LIB_INC)

# Our favourite
all: $(OBJDIR) $(PROJECT)

mnt_sshfs:
	$(MKDIR) $(TARGET_FS)
	$(SSHFS) $(DEPLOY_USER)@$(DEPLOY_IP):/ $(TARGET_FS) -o transform_symlinks 

umnt_sshfs:
	$(UMOUNT) $(TARGET_FS)

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

