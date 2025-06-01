all: vitrader
vitrader:
	g++ -std=c++11 -I./CTP -I./INIReader -L/lib64 -o $@ ViTrader.cpp ini.cpp INIReader.cpp thosttraderapi_se.so thostmduserapi_se.so -lcurses -ltinfo
clean:
	rm vitrader

