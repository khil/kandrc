CC = clang
CFLAGS = -Wall -Werror
LIBS = -lm
EXE_FILE = ex4-11

final : main.o cmd.o getch.o getop.o stack.o
	$(CC) $(CFLAGS) -o $(EXE_FILE) main.o cmd.o getch.o getop.o stack.o $(LIBS)
main.o : main.c calc.h
	$(CC) $(CFLAGS) -c main.c
cmd.o : cmd.c calc.h
	$(CC) $(CFLAGS) -c cmd.c
getch.o : getch.c calc.h
	$(CC) $(CFLAGS) -c getch.c
getop.o : getop.c calc.h
	$(CC) $(CFLAGS) -c getop.c
stack.o : stack.c calc.h
	$(CC) $(CFLAGS) -c stack.c
clean :
	rm *.o $(EXE_FILE)

