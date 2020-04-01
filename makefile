all : list.o buddy_system.o main.o
	gcc -g ./*.o
	rm ./*.o
list.o : list.h list.c
	gcc -c -g list.c

buddy_system.o : buddy_system.h buddy_system.c
	gcc -c -g buddy_system.c

main.o : main.c
	gcc -c -g main.c