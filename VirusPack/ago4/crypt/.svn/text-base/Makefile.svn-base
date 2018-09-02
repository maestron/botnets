CC = gcc -ansi -pipe
CXX = g++ -ansi -pipe
CFLAGS = -DLINUX
LDFLAGS = 
OBJS = main.o
FNAME = crypt

all: $(OBJS) link fin

cleanbin: clean $(OBJS) link fin

link:
	$(CC) -o $(FNAME) $(OBJS) -lstdc++

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

clean:
	@rm -f *.o

fin:
	@mkdir -p ../bin/linux
	@cp $(FNAME) ../bin/linux
