# Modified Makefile to allow for building of the standalone module

TITLE=libnss_identity

CC = gcc
LIBSRC = $(TITLE).c
LIBOBJ = $(TITLE).o
LIBSHARED = $(TITLE).so.2

all: $(LIBSHARED)

$(LIBSHARED): $(LIBOBJ)
		ld -x --shared -o $@ $(LIBOBJ)

clean:
	rm -f $(LIBOBJ) $(LIBSHARED) core *~

extraclean: clean
	rm -f *.a *.o *.so *.bak 

.c.o:
	$(CC) -fPIC -c $< -o $@
