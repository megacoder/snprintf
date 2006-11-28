CC		=ccache gcc4 -march=i686 -std=gnu99
DEFS	=-D_FORTIFY_SOURCE=2
OPT		=-Os
INCL	=-I.
CFLAGS	=${OPT} ${DEFS} ${INCL} -Wall -Wextra -Werror -pedantic -g
LDFLAGS	=-g

.SUFFIXES: .lst .s .c

%${OPT}.s: %.c
	${CC} ${CFLAGS} -S -o $@ $^

%${OPT}.lst: %.o
	objdump -dS $^ >$@

CFILES	=snprintf.c
SFILES=${CFILES:.c=${OPT}.s}
LSTFILES=${CFILES:.c=${OPT}.lst}

all:	snprintf ${SFILES} ${LSTFILES}

snprintf.o: snprintf.c
	${CC} ${CFLAGS} -c -o $@ $^

snprintf: snprintf.o
	${CC} ${LDFLAGS} -o $@ $^

clean:
	${RM} *.s *.lst *.o

distclean clobber: clean
	${RM} snprintf

check::	snprintf
	./snprintf ${ARGS}
