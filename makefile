CC     = g++
IDIR   = .
CFLAGS = -I$(IDIR) -std=c++11
OBJS   = main.o

medusa: $(OBJS)
	$(CC) -o medusa $(OBJS) $(CFLAGS) -lpthread

main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)

.PHONY: clean

clean:
	rm medusa $(OBJS)
