CC = g++ -std=c++11
UTILSHPP = src/Utils.hpp
UTILSCPP = src/Utils.cpp
LIBS = `pkg-config --libs --cflags opencv`

all: ShotFG

Utils.o: $(UTILSHPP) $(UTILSCPP)
	@$(CC) -o src/$@ -c $(UTILSCPP)

ShotFG: src/Utils.o src/main.cpp
	@$(CC) src/main.cpp src/Utils.o -o ShotFG $(LIBS)

clean:
	@rm -f ShotFG src/*.o
