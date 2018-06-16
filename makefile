# Tristan Hilbert 6/10/2016
#

EXE := prog
DEXE := d_prog
FLAGS := -pedantic -ansi
SOURCE_FILES := $(wildcard */*.c) $(wildcard *.c)
OBJECTS = $(SOURCE_FILES:%.c=%.o)

all: $(EXE)

clean:
	rm -f -r $(OBJECTS)
	rm -f $(EXE)
	rm -f $(DEXE)


.c.o:
	gcc $(FLAGS) -c $< -o $@

$(EXE): $(OBJECTS)
	gcc $(FLAGS) $(OBJECTS) -o $@

debug: 
	gcc $(SOURCE_FILES) -g -o $(DEXE)
