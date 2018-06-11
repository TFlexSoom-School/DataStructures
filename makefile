# Tristan Hilbert 6/10/2016
#

EXE := prog
FLAGS := -pedantic -ansi
SOURCE_FILES := $(wildcard */*.c)
OBJECTS = $(SOURCE_FILES:%.c=%.o)

all: $(EXE)

clean:
	rm -f -r $(OBJECTS)
	rm -f $(EXE)


.c.o:
	gcc $(FLAGS) $< -o $@

$(EXE): $(OBJECTS)
	gcc $(FLAGS) $(OBJECTS) -o $@

