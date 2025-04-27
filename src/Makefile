CC=gcc
CFLAGS=-g -Wall -O2
LDFLAGS=-lpthread
TARGET=ThreadCoin
SOURCES=main.c threadcoin.c queue.c
OBJECTS=$(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

main.o: main.c threadcoin.h queue.h
	$(CC) $(CFLAGS) -c $< -o $@

threadcoin.o: threadcoin.c threadcoin.h queue.h
	$(CC) $(CFLAGS) -c $< -o $@

queue.o: queue.c threadcoin.h queue.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

clean_all:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean clean_all
