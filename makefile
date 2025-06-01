# Connect 4 makefile
# ./connect4

DEFINES =
DEBUG = -g
WERROR =
CFLAGS = -Wall -I/opt/homebrew/opt/raylib/include \
	$(WERROR) $(DEBUG) $(DEFINES)

CXX = g++ $(CFLAGS) -std=c++17
PROG = connect4
LIBS = -L/opt/homebrew/opt/raylib/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

all: $(PROG)

$(PROG): main.o connect4.o ui.o
	$(CXX) -o $@ $^ $(LIBS)

main.o: main.cpp ui.h connect4.h
	$(CXX) -c $<

connect4.o: connect4.cpp connect4.h
	$(CXX) -c $<

ui.o: ui.cpp ui.h connect4.h
	$(CXX) -c $<

clean:
	rm -f *.o $(PROG)

.PHONY: all clean
