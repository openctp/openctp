UNAME_S := $(shell uname -s)

INC_DIRS = -I. -ICLI -Inlohmann -ITinyXML2

COMMON_SRCS = TinyXML2/tinyxml2.cpp
COMMON_OBJS = $(COMMON_SRCS:.cpp=.o)

ALL_TARGETS = ctpprice ctpoptprice ctporder ctpoptorder

ifeq ($(UNAME_S),Darwin)
    # ========== MacOS ==========
    CXX = clang++
    CXXFLAGS = -std=c++11 -Wall -O2 $(INC_DIRS) -ICTPAPI_MacOS
    CTP_DIR = $(CURDIR)/CTPAPI_MacOS
    
    # No opt support for Mac
    ALL_TARGETS = ctpprice ctporder
    
    # CTP LIBS
    MD_LIB = $(CTP_DIR)/libthostmduserapi_se.a
    TD_LIB = $(CTP_DIR)/libthosttraderapi_se.a
    COMMON_LIBS = $(CTP_DIR)/comunicationkeylib.a $(CTP_DIR)/libcrypto.a $(CTP_DIR)/libssl.a
    
    LIBS_CTPPRICE = $(MD_LIB) $(COMMON_LIBS)
    LIBS_CTPORDER = $(TD_LIB) $(COMMON_LIBS)

else ifeq ($(UNAME_S),Linux)
    # ========== Linux ==========
    CXX = g++
    CTP_CXXFLAGS = -std=c++11 -Wall -O2 $(COMMON_INC_DIRS) -I$(CTP_DIR)
    OPT_CXXFLAGS = -std=c++11 -Wall -O2 $(COMMON_INC_DIRS) -I$(OPT_DIR)
    CTP_DIR = $(CURDIR)/CTPAPI_Linux
    OPT_DIR = $(CURDIR)/CTPOPT_Linux
    
    # CTP LIBS
    MD_LIB = $(CTP_DIR)/thostmduserapi_se.so
    TD_LIB = $(CTP_DIR)/thosttraderapi_se.so
    OPT_MD_LIB = $(OPT_DIR)/soptthostmduserapi_se.so
    OPT_TD_LIB = $(OPT_DIR)/soptthosttraderapi_se.so
    
    LIBS_CTPPRICE = $(MD_LIB)
    LIBS_CTPORDER = $(TD_LIB)
    LIBS_CTPOPTPRICE = $(OPT_MD_LIB)
    LIBS_CTPOPTORDER = $(OPT_TD_LIB)
endif

all: $(ALL_TARGETS)

# ---------- ctpprice ----------
ctpprice: ctpprice.o $(COMMON_OBJS)
	$(CXX) $(CTP_CXXFLAGS) -o $@ $^ $(LIBS_CTPPRICE)

# ---------- ctpoptprice ----------
ifeq ($(UNAME_S),Linux)
ctpoptprice: ctpoptprice.o $(COMMON_OBJS)
	$(CXX) $(OPT_CXXFLAGS) -o $@ $^ $(LIBS_CTPOPTPRICE)
endif

# ---------- ctporder ----------
ctporder: ctporder.o $(COMMON_OBJS)
	$(CXX) $(CTP_CXXFLAGS) -o $@ $^ $(LIBS_CTPORDER)

# ---------- ctpoptorder ----------
ifeq ($(UNAME_S),Linux)
ctpoptorder: ctpoptorder.o $(COMMON_OBJS)
	$(CXX) $(OPT_CXXFLAGS) -o $@ $^ $(LIBS_CTPOPTORDER)
endif

# CTPAPI
ctpprice.o: ctpprice.cpp
	$(CXX) $(CTP_CXXFLAGS) $(INC_DIRS) -c $< -o $@

ctporder.o: ctporder.cpp
	$(CXX) $(CTP_CXXFLAGS) $(INC_DIRS) -c $< -o $@

# CTPOPT
ifeq ($(UNAME_S),Linux)
ctpoptprice.o: ctpoptprice.cpp
	$(CXX) $(OPT_CXXFLAGS) $(INC_DIRS) -c $< -o $@

ctpoptorder.o: ctpoptorder.cpp
	$(CXX) $(OPT_CXXFLAGS) $(INC_DIRS) -c $< -o $@
endif

# Common objs
TinyXML2/tinyxml2.o: TinyXML2/tinyxml2.cpp
	$(CXX) $(COMMON_INC_DIRS) -std=c++11 -O2 -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o TinyXML2/*.o $(ALL_TARGETS)

.PHONY: all clean
