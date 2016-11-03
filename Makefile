PROG := 5-4
SRCS := $(PROG).c xfunc.c iip.c
#SRCS := $(PROG).c xfunc.c
OBJS := $(SRCS:%.c=%.o)
DEPS := $(SRCS:%.c=%.d)

CC := gcc
CFLAGS := -Wall -g -MMD

all: $(PROG)

-include $(DEPS)

$(PROG): $(OBJS)
	$(CC) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) -c $^

run:
	./$(PROG)

clean:
	rm -fr $(PROG) $(OBJS) $(DEPS)

#xfunc.o: xfunc.c
#	$(CC) -Wall -c -o xfunc.o xfunc.c -g
#
#$(PROG).o: $(PROG).c
#	$(CC) -Wall -c -o $(PROG).o $(PROG).c -g
#
#iip.o: iip.c
#	$(CC) -Wall -c -o iip.o iip.c -g

