CFLAGS+=  -pedantic -g -Wall -std=c99 -O3 
HW=hw04-b0b36prp
ZIP=zip

$(HW): main.c 
	$(CC) $(CFLAGS) main.c -o $(HW) -lm

zip:
	$(ZIP) $(HW)-brute.zip main.c

clean:
	$(RM) -f *.o
	$(RM) -f $(HW)
	$(RM) -f $(HW)-brute.zip

.PHONY: clean zip
