all:
	g++ -std=c++0x -pthread -o server server.cpp
	g++ -std=c++0x -o client client.cpp
