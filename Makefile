CFLAGS = -Wall -Wextra

all : cfv1

lota.o : lota.c lota.h
	gcc -c $(CFLAGS) lota.c

lotb.o : lotb.c lotb.h lota.h
	gcc -c $(CFLAGS) lotb.c

lotc.o : lotc.c lotc.h lotb.h
	gcc -c $(CFLAGS) lotc.c

main.o : main.c lota.h lotb.h lotc.h
	gcc -c $(CFLAGS) main.c 

cfv1 : main.o lota.o lotb.o lotc.o
	gcc -o cfv1 main.o lota.o lotb.o lotc.o 


doc :
	doxygen -g 
