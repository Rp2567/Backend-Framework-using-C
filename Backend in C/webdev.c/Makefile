flags=-02 -Wall -std=c2x
ldflags=
tmp = birchutils.o

.PHONY: all clean

all: clean webdev

webdev: webdev.o
	cc $(flags) $< -o $@ $(ldflags) $(tmp)

webdev.o : webdev.c webdev.h
	cc $(flags) -c $<

clean:
	rm -rf webdev *.o