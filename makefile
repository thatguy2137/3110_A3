all:
	gcc -std=c99 -pthread dine.c -o dine.out;
	gcc -std=c99 holes.c -o holes.out

