
#PREFIX = /usr/bin
#HOST = arm-linux-gnueabihf

ifndef PREFIX
  PREFIX = .
endif

#Compiler
CC = g++

#Strip
STRIP = strip

ifdef HOST
	CC = $(HOST)-g++
	STRIP = $(HOST)-strip
endif


#OBJECT
OBJECT = $(PREFIX)/bin/rfid_test
#DEFINITIONS
DEFS = -DTRACES_VERIFICATION
DEFS += -DDEBUG_TRACES
DEFS += -std=gnu++1y

#Source Files
SOURCE_FILE = ./main.cpp
SOURCE_FILE += ./src/SerialDevice.cpp ./src/RFIDDevice.cpp ./src/RFIDMessage.cpp ./src/MessageRFIDBody.cpp ./src/RFID.cpp

#INCLUDE

INCLS = -I./src

all:
	$(CC) -Wall $(DEFS) -o$(OBJECT) $(SOURCE_FILE) $(INCLS) $(LIBS)
	$(STRIP) $(OBJECT)
