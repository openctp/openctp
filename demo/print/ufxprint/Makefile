CXX 			= g++
CXX_FLAGS 		= -w -Wextra -std=c++11 -pthread -ggdb -g
OS_NAME			= $(shell uname -s)
DEFS			=
INCLUDES 		= UFX
LIB_DIRS 		= /
LIBRARIES 		= -lt2sdk
TARGET 			= ufx


ifeq ($(findstring Linux, $(OS_NAME)), Linux)
	DEFS		+= LINUX
endif

all : $(TARGET)

run: clean all
	clean
	./$(TARGET)

$(TARGET): ./ufxprint.cpp ./UFX/*cpp
	$(CXX) $(CXX_FLAGS) -D$(DEFS) -I$(INCLUDES) -L$(LIB_DIRS) $^ -o $@ $(LIBRARIES)

clean:
	-rm -f $(TARGET)