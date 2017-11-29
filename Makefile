CC		= gcc
CFLAGS		= -Wall -Wextra -Werror -std=c99 -pedantic -pedantic-errors
CFLAGS		+= -O2 -march=native
PROGNAME	= sortedstacks
OBJS=$(PROGNAME).o

.PHONY: all clean clean-all

all: $(PROGNAME)

$(PROGNAME): $(OBJS)

$(OBJS): $(PROGNAME).c

clean:
	-@rm $(OBJS) ./*~ ./.*~
clean-all: clean
	-@rm $(PROGNAME)
