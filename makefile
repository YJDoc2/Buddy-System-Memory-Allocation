all : list.o buddy_system.o main.o virtual_mem.o
	gcc -g ./*.o
	rm ./*.o

list.o : list.h list.c
	gcc -c -g list.c

virtual_mem.o : virtual_mem.c virtual_mem.h
	gcc -c -g virtual_mem.c
	
buddy_system.o : buddy_system.h buddy_system.c
	gcc -c -g buddy_system.c

main.o : main.c
	gcc -c -g main.c