OBJS = integer.o test-integer.o da.o stack.o cda.o queue.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : test-integer stacktest datest cdatest queuetest


cdatest: cdatest.c integer.o cda.o
		gcc $(LOPTS) cdatest.c integer.o cda.o -o cdatest

datest : datest.c integer.o da.o
	gcc $(LOPTS) datest.c integer.o da.o -o datest

stacktest: stacktest.c stack.o integer.o da.o
		gcc $(LOPTS) stacktest.c integer.o da.o stack.o -o stacktest


queuetest: queuetest.c queue.o integer.o cda.o
		gcc $(LOPTS) queuetest.c integer.o cda.o queue.o -o queuetest

queue.o: queue.c queue.h
		gcc $(OOPTS) queue.c cda.c

cda.o: cda.c cda.h
	gcc $(OOPTS) cda.c 

stack.o:  stack.c stack.h 
		gcc $(OOPTS) stack.c da.c
		
datest.o : datest.c 
		gcc $(OOPTS) datest.c da.c

da.o : da.c da.h
		gcc $(OOPTS) da.c 

test-integer : $(OBJS)
		gcc $(LOPTS) $(OBJS) -o test-integer

integer.o : integer.c integer.h
		gcc $(OOPTS) integer.c

test-integer.o :	test-integer.c integer.h
		gcc $(OOPTS) test-integer.c

test : test-integer 
		./test-integer ./da ./stacktest ./cdatest ./queuetest

valgrind : test-integer cdatest stacktest queuetest datest
		valgrind ./test-integer
		valgrind ./datest
		valgrind ./cdatest
		valgrind ./queuetest

clean	:
		rm -f $(OBJS) test-integer datest stacktest cdatest queuetest
		