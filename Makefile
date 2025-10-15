build:
	gcc -o lru main.c
clean:
	rm -f lru
	rm -f cache_data.txt