CC := gcc
# no c flags rip
LIB := -lcrypto
GEN := general.c

%: %.c $(GEN)
	$(CC) $^ $(LIB)
	@echo "MADE $@ as a.out"

clean: 
	rm a.out