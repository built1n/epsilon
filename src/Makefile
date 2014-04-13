SOURCES = read.o main.o
HEADERS = object.h read.h room.h
all: $(SOURCES)  $(HEADERS) Makefile
	g++ $(SOURCES) -O3 -o epsilon
clean:
	rm -rf *.o
	rm -rf *~
	rm -rf a.out
