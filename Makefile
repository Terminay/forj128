CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lm

all: forj128_cli avalanche_test libforj128.so

forj128_cli: main.c forj128.c forj128.h
	$(CC) $(CFLAGS) main.c forj128.c -o forj128_cli $(LDFLAGS)

avalanche_test: avalanche_test.c forj128.c forj128.h
	$(CC) $(CFLAGS) avalanche_test.c forj128.c -o avalanche_test $(LDFLAGS)

test_forj128: tests/test_forj128.c forj128.c forj128.h
	$(CC) $(CFLAGS) tests/test_forj128.c forj128.c -o test_forj128 $(LDFLAGS)

test: test_forj128
	./test_forj128

libforj128.so: forj128.c forj128.h
	$(CC) $(CFLAGS) -fPIC -shared forj128.c -o libforj128.so $(LDFLAGS)

clean:
	rm -f forj128_cli avalanche_test test_forj128 libforj128.so

.PHONY: all clean test
