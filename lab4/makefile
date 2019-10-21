CC=gcc
CFLAGS=

n1: clean
	$(CC) $(CFLAGS) n1.c -o lab
n2: clean
	$(CC) $(CFLAGS) n2.c -o lab
n3: clean
	$(CC) $(CFLAGS) n3.c -o lab
n4: clean
	$(CC) $(CFLAGS) n4.c -o lab
n5: clean pcheck
	$(CC) $(CFLAGS) -c n5.c -o n5.o
	$(CC) $(CFLAGS) n5.o pcheck.o -o lab
n6: clean pcheck
	$(CC) $(CFLAGS) -c n6.c -o n6.o
	$(CC) $(CFLAGS) -c n6_srv.c -o n6s.o
	$(CC) $(CFLAGS) n6.o pcheck.o -o labc
	$(CC) $(CFLAGS) n6s.o pcheck.o -o labs
n7: clean pcheck
	$(CC) $(CFLAGS) -c n7.c -o n7.o
	$(CC) $(CFLAGS) n7.o pcheck.o -o lab
n8: clean pcheck
	$(CC) $(CFLAGS) -c n8.c -o n8.o
	$(CC) $(CFLAGS) n8.o pcheck.o -o lab
n9: clean pcheck
	$(CC) $(CFLAGS) -c n9.c -o n9.o
	$(CC) $(CFLAGS) n9.o pcheck.o -o lab

n10: clean pcheck
	$(CC) $(CFLAGS) -c n10.c -o n10.o
	$(CC) $(CFLAGS) n10.o pcheck.o -o lab
n11: clean pcheck
	$(CC) $(CFLAGS) -c n11.c -o n11.o
	$(CC) $(CFLAGS) n11.o pcheck.o -o lab

clean:
	rm -f *.o lab* a.out file slp prog matrix
pcheck:
	$(CC) $(CFLAGS) -c pcheck.c -o pcheck.o
