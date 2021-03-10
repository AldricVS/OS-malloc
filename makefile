#======= Variables =======#

# All dependencies that main need
OBJ = MyBlock.o MyMemory.o
# name of the main file and the output app
EXEC = osAlloc

GCC_FLAGS = -Wall

#Special command to force execution of those target, even if already exists
.PHONY: $(EXEC) doc

#======= Commands =======#

# Default command
all: $(EXEC) clean

# For the documentation
doc: 
	doxygen Doxyfile

# Compile with all dependencies and all warnings activated
$(EXEC):
	# Create all object files from all c files (except the main one)
	gcc -c $(filter-out $(EXEC).c,$(wildcard *.c))
	# Compile the app executable
	gcc $(GCC_FLAGS) *.o $(EXEC).c -o $(EXEC)

clean: 
	# Delete all object files 
	rm -f *.o
