all: server_threads server_libev  client

server_threads: server_threads.c
	gcc -o $@ $< -O2 -pthread

server_libev: server_libev.c
	gcc -o $@ $< -lev -O2 --std=gnu99

client: client.c
	gcc -o $@ $< -O2 -g -pthread -lrt --std=gnu99
