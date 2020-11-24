PROG=lines
CONFIG=`pkg-config allegro-5 allegro_primitives-5 --libs --cflags`

all: $(PROG)

run: all
	@./$(PROG)

$(PROG): $(PROG).o
	gcc -o $(PROG) $(PROG).o $(CONFIG)

$(PROG).o: $(PROG).c
	gcc -c $(PROG).c

.phony: clean run

clean:
	@rm -f *.o $(PROG)
