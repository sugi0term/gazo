target = 3-3

all: xfunc.o $(target).o
	gcc -o $(target) $(target).o xfunc.o -g

run:
	./$(target)

clean:
	rm -fr $(target) $(target).o xfunc.o

xfunc.o: xfunc.c
	gcc -c -o xfunc.o xfunc.c -g

$(target).o: $(target).c
	gcc -c -o $(target).o $(target).c -g
