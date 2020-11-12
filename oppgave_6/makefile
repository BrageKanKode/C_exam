# Makefile template


INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I$(INCLDIR)
THREAD = -lpthread

OBJDIR = obj

_DEPS = main.h

DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = main.o
OBJS = $(patsubst %, $(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJS)
	gcc -o $@ $^ $(CFLAGS) $(THREAD)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)*~