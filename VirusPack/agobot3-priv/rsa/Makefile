CC = gcc -ansi -pipe
CFLAGS = -DLINUX
LDFLAGS = 
OBJS = desc.o digit.o md2c.o md5c.o nn.o prime.o r_dh.o r_encode.o r_enhanc.o r_keygen.o r_random.o r_stdlib.o rsa.o

all: $(OBJS)

cleanbin: clean $(OBJS)

desc.o: desc.c
	$(CC) $(CFLAGS) -c desc.c

digit.o: digit.c
	$(CC) $(CFLAGS) -c digit.c

md2c.o: md2c.c
	$(CC) $(CFLAGS) -c md2c.c

md5c.o: md5c.c
	$(CC) $(CFLAGS) -c md5c.c

nn.o: nn.c
	$(CC) $(CFLAGS) -c nn.c

prime.o: prime.c
	$(CC) $(CFLAGS) -c prime.c

r_dh.o: r_dh.c
	$(CC) $(CFLAGS) -c r_dh.c

r_encode.o: r_encode.c
	$(CC) $(CFLAGS) -c r_encode.c

r_enhanc.o: r_enhanc.c
	$(CC) $(CFLAGS) -c r_enhanc.c

r_keygen.o: r_keygen.c
	$(CC) $(CFLAGS) -c r_keygen.c

r_random.o: r_random.c
	$(CC) $(CFLAGS) -c r_random.c

r_stdlib.o: r_stdlib.c
	$(CC) $(CFLAGS) -c r_stdlib.c

rsa.o: rsa.c
	$(CC) $(CFLAGS) -c rsa.c

clean:
	@rm -f *.o
