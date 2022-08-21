.DEFAULT_GOAL := run

compile: 
	cc parser.c util.c osh.c -o osh.o

run: compile
	./osh.o

cleanup: 
	rm -f ./*.txt
	rm -f ./*.o

main.o: 
	cc main.c -o main.o

test: main.o 
	./main.o
	