all:
	g++ main.cpp logfileParser.cpp logfileUtils.cpp -std=c++14 -O2 -o parser.exe