all:
	arm-poky-linux-gnueabi-gcc -g -c main.S -o main.o
	arm-poky-linux-gnueabi-ld -Ttext 0x80800000 main.o -o main
clean:
	rm *.o main
