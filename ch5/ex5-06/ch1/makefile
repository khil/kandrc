CC = clang
CFLAGS = -std=c99 -Wall -Werror
LIBS = 

ifndef FILE
$(error   Parm FILE is required.  ex: make FILE=filename.c)
else
F = $(basename $(FILE))
$(info    Making $(F))
endif


$(F) : $(F).o str.o
	$(CC) $(CFLAGS) -o ../bin/$(F) $(F).o str.o
	rm *.o
str.o : 
	$(CC) $(CFLAGS) -c ../str.c
$(F).o : 
	$(CC) $(CFLAGS) -c ./$(F).c
clean :
	rm *.o

