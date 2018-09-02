CC = gcc -ansi -pipe
CXX = g++ -ansi -pipe
CFLAGS = -DLINUX
LDFLAGS = 
OBJS = md5c.o r_random.o main.o
FNAME = getmd5



all: $(OBJS) link fin

cleanbin: clean $(OBJS) link fin

link:
	$(CC) -o $(FNAME) $(OBJS) -lstdc++

md5c.o: md5c.c
	$(CC) $(CFLAGS) -c md5c.c

r_random.o: r_random.c
	$(CC) $(CFLAGS) -c r_random.c

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp

clean:
	@rm -f *.o

fin:
	@mkdir -p ../bin/linux
	@cp $(FNAME) ../bin/linux
