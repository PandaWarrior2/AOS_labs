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
n5: clean
	$(CC) $(CFLAGS) n5.c -o lab
n6: clean
	$(CC) $(CFLAGS) n6_client.c -o client
	$(CC) $(CFLAGS) n6.c -o srv
n8: clean
	$(CC) $(CFLAGS) n8.c -o srv
	$(CC) $(CFLAGS) n8_client.c -o client
n9: clean
	$(CC) $(CFLAGS) n9.c -o srv
	$(CC) $(CFLAGS) n9_client.c -o client
n10: clean
	$(CC) $(CFLAGS) n10.c -o srv
	$(CC) $(CFLAGS) n10_client.c -o client
n11: clean
	$(CC) $(CFLAGS) n11.c -o lab

clean:
	rm -f *.o lab* a.out file slp prog matrix srv client
