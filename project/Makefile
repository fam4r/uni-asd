CC=gcc
CFLAGS=
LIBS=

ODIR=obj

DEPS = hash.h bloom.h

_OBJ = hash.o bloom.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main.exe: $(OBJ)
	$(CC) -o $@ main.c $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core main
