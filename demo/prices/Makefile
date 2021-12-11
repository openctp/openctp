all: TextTrader
TextTrader:
	g++ -std=c++11 -I./CTP -L/lib64 -o $@ TextTrader.cpp thostmduserapi_se.so -lcurses -ltinfo
clean:
	rm TextTrader

