OBJ = MyBlock.o MyMemory.o

EXEC = osAlloc

all: $(EXEC) clean

$(EXEC): $(OBJ)
	gcc $(OBJ) $(EXEC).c -o $(EXEC)

clean: 
	rm -f *.o