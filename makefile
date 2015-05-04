CC     = g++
IDIR   = .
CFLAGS = -I$(IDIR) -std=c++11
OBJS   = main.o

medusa: $(OBJS)
	$(CC) -o medusa $(OBJS)

main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm medusa $(OBJS)
