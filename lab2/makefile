CC=gcc
CFLAGS=

n1: clean
	$(CC) $(CFLAGS) n1.c -o lab
n2: clean
	$(CC) $(CFLAGS) n2.c -o lab
n3: clean
	$(CC) $(CFLAGS) n3.c -o lab
n4: clean slp
	$(CC) $(CFLAGS) -DKILL=1 n4.c -o lab
n5: clean slp
	$(CC) $(CFLAGS) -DKILL=0 n5.c -o lab
n6: clean slp
	$(CC) $(CFLAGS) n6.c -o lab
n7: clean slp
	$(CC) $(CFLAGS) n7.c -o lab

n8: clean
	rm -f out_parent out_child
	$(CC) $(CFLAGS) n8.c -o lab

n9: clean
	rm -f out_parent out_child
	$(CC) $(CFLAGS) n9.c -o lab

n10: clean
	$(CC) $(CFLAGS) n10.c -o lab
n11: clean
	$(CC) $(CFLAGS) n11.c -o lab
clean:
	rm -f lab a.out file slp
slp: clean
	$(CC) $(CFLAGS) slp.c -o slp
