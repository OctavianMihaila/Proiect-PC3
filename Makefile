build: 
	gcc -g -Wall -o main main.c functions.c functions_aditional.c
run:
	./main
clean:
	rm -f *.o main
