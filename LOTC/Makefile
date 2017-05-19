CFLAGS = -Wall -Wextra

all : cfv1

lota.o : lota.c lota.h
	gcc -c $(CFLAGS) lota.c

lotb.o : lotb.c lotb.h lota.h
	gcc -c $(CFLAGS) lotb.c

lotbgraphique.o : lotbgraphique.c lotbgraphique.h lotb.h
	gcc -c  $(CFLAGS) lotbgraphique.c -lSDL	-lSDL_ttf

lotc.o : lotc.c lotc.h lotbgraphique.h
	gcc -c $(CFLAGS) lotc.c -lSDL -lSDL_ttf

main.o : main.c lota.h lotb.h lotbgraphique.h lotc.h
	gcc -c $(CFLAGS) main.c -lSDL -lSDL_ttf

cfv1 : main.o lota.o lotb.o lotbgraphique.o lotc.o
	gcc -o cfv1 main.o lota.o lotb.o lotbgraphique.o lotc.o -lSDL -lSDL_ttf

doc :
	doxygen -g 
