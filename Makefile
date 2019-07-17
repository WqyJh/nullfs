CC = gcc
SRCS = nullfs.c

build: $(SRCS)
	$(CC) $(SRCS) -o nullfs `pkg-config fuse --cflags --libs`

clean:
	rm nullfs
