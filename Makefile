#Compile:
calendar : main.o
	gcc -o calendar main.o
main.o : main.c
	gcc -c main.c
