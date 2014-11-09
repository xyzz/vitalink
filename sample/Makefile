CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld

OBJS = start.o main.o

homebrew.elf: $(OBJS) __stubs.o
	$(LD) -n -T link.lds $^ -o $@.tmp
	vitalink --fixup $@.tmp
	mv $@.tmp $@

__stubs.o: __stubs.S
	$(AS) $< -o $@

__stubs.S: $(OBJS)
	vitalink nids.xml $^

main.o: main.c
	$(CC) -c $< -o $@

clean:
	-rm -f *.o *.elf __stubs.S
