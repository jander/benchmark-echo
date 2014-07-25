#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <string.h>  // strlen memset
#include <errno.h>   // perror
#include <pthread.h>
#include <fcntl.h>     //fcntl

#define MAX_BACKLOG 32
#define BUFFER_SIZE 10240
#define PORT_NO 5000

int new_tcp_server(const char *host, short port);

void* echo_handler(void *);

int set_address (const char *host, short port, struct sockaddr_in *addr);

int set_reuse_socket(int sock);


int main (int argc , char *argv[])
{
	int fd;

	int port = PORT_NO;
	if(argc==2){
		port = atoi(argv[1]);
	}else if(argc != 1 && argc != 2){
		fprintf(stderr, "usage: server_threads [port]\n");
        return 1;
	}

	fd = new_tcp_server("0.0.0.0", port);
	if (fd < 0) {
		return -1;
	}

	printf("Starting tcp server on :%d\n", port);

	for(;;) {
		struct sockaddr_in addr;
		socklen_t addrlen = sizeof(struct sockaddr_in);

		int *client_fd;
		pthread_t thread;
		pthread_attr_t thread_attr;

		client_fd = (int *)malloc(sizeof(int));

		*client_fd = accept(fd, (struct sockaddr *)&addr, (socklen_t*)&addrlen);
		if (*client_fd == -1) {
			perror("accept");
			free(client_fd);
			break;
		}

        pthread_attr_init(&thread_attr);
        pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

		if( pthread_create(&thread, &thread_attr, echo_handler, (void*) client_fd) < 0) {
			perror("pthread_create");
			free(client_fd);
			close(*client_fd);
			break;
		}
	}

	close(fd);

	return 0;
}


void* echo_handler(void* client_fd)
{
	int len;

	char* buffer = malloc(BUFFER_SIZE);

	//Get the fd
	int fd = *(int*)client_fd;

	for(;;) {
		memset(buffer, 0, BUFFER_SIZE);

		len = read(fd, buffer, BUFFER_SIZE);

		if(len < 0) {
			perror("read");
			break;
		} else if (len == 0) {
			//disconnected!
			break;
		}

		len = write(fd, buffer, strlen(buffer));

		if(len < 0) {
			perror("write");
			break;
		} else if (len == 0) {
			//disconnected!
			break;
		}
	}

	free(buffer);
	free(client_fd);
	close(fd);
	pthread_exit(NULL);
}


int new_tcp_server(const char *host, short port)
{
	int fd;
	struct sockaddr_in address;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1) {
		perror("socket");
		return -1;
	}

	set_reuse_socket(fd);

	set_address(host, port, &address);

	if (bind(fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		perror("bind");
		close(fd);
		return -1;
	}

	if (listen(fd, MAX_BACKLOG) <0){
		perror("listen");
		close(fd);
		return -1;
	};

	return fd;
}


int set_address (const char *host, short port, struct sockaddr_in *addr)
{
	memset(addr, 0, sizeof(*addr));
	addr->sin_family  = AF_INET;
	addr->sin_addr.s_addr = inet_addr(host);
	addr->sin_port = htons(port);
	return 0;
}


int set_reuse_socket(int sock)
{
	int ok = 1;
	return setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(ok));
}