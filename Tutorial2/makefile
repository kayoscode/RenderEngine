IDIR =include
CC=g++
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =../lib

LIBS=-lm -lncurses

_DEPS=defs.h Vector2.h Vector3.h Vector4.h
DEPS= $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=main.o Vector2.o Vector3.o Vector4.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

run: all
	./all
