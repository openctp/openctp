all: prices
prices:
	g++ -std=c++11 -I./CTP -L/lib64 -o $@ prices.cpp thostmduserapi_se.so -lcurses -ltinfo
clean:
	rm prices

