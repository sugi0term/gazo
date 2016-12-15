PART := 10
QUES := 5
PROG := $(PART)-$(QUES)
SRCS := $(PROG).c $(PART).c xfunc.c iip.c
# SRCS := $(PROG).c xfunc.c iip.c
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
