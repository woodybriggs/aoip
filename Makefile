all: myapp

myapp: myapp.c
	$(CC) -o $@ $< `pkg-config --cflags --libs libpjproject`

clean:
	rm -f myapp.o myapp
