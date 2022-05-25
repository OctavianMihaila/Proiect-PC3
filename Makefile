build: 
	gcc -g -Wall -o main main.c functions.c
run:
	./main
clean:
	rm -f *.o main
