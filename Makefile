build: 
	gcc -g -Wall -o main main.c functions.c functions_aditional.c QueueFunctions.c
run:
	./main
clean:
	rm -f *.o main
