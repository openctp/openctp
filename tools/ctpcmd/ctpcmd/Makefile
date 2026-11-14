UNAME_S := $(shell uname -s)

TARGET = ctpprice
SRCS = ctpprice.cpp TinyXML2/tinyxml2.cpp
OBJS = $(SRCS:.cpp=.o)

INC_DIRS = -I. -ICLI -Inlohmann -ITinyXML2

ifeq ($(UNAME_S),Darwin)
    CXX = clang++
    CXXFLAGS = -std=c++11 -Wall -O2 $(INC_DIRS) -ICTPAPI_MacOS
    CTP_DIR = $(CURDIR)/CTPAPI_MacOS
    LIBS = $(CTP_DIR)/libthostmduserapi_se.a \
           $(CTP_DIR)/comunicationkeylib.a \
           $(CTP_DIR)/libcrypto.a \
           $(CTP_DIR)/libssl.a
           
else ifeq ($(UNAME_S),Linux)
    CXX = g++
    CXXFLAGS = -std=c++11 -Wall -O2 $(INC_DIRS) -ICTPAPI_Linux
    CTP_DIR = $(CURDIR)/CTPAPI_Linux
    LIBS = $(CTP_DIR)/thostmduserapi_se.so
endif

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
