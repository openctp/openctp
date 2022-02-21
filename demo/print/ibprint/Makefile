CXX=g++
CXXFLAGS=-pthread -Wall -Wno-switch -Wpedantic -std=c++11
BASE_SRC_DIR=./IB
INCLUDES=-I${BASE_SRC_DIR}
SHARED_LIB_DIRS=-L${BASE_SRC_DIR}
SHARD_LIBS=-lTwsSocketClient
TARGET1=libTwsSocketClient.so
TARGET=IB

$(TARGET):
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BASE_SRC_DIR)/*.cpp -fPIC -shared -o $(TARGET1)
	$(CXX) $(CXXFLAGS) $(INCLUDES) IB.cpp -L. $(SHARD_LIBS) -o$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET1) *.o