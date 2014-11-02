CC=gcc
SRC=tema2.c
EXE=tema2
CFLAGS=-Wall


build:
	$(CC) $(SRC) -o $(EXE) $(CFLAGS)

.PHONY:clean	

clean:
	rm -f $(EXE)


