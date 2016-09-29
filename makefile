
bst: test.o bst.c
	gcc bst.c test.o -o bst

test.o: test.c bst.h
	gcc -c test.c

clean:
	rm -f *.o bst


