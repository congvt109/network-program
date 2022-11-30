main: HW1.o LL.o
	gcc -o main HW1.o LL.o
HW1.o: 	HW1.c LL.h
		gcc -c HW1.c
LL.o: 	LL.c LL.h
		gcc -c LL.c
clean: 
	rm all main.o