#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ev.h>

#define PORT_NO 5000
#define BUFFER_SIZE 10240
#define MAX_BACKLOG 1024

int total_clients = 0;

void on_accept(struct ev_loop *loop, struct ev_io *watcher, int revents);
void on_read(struct ev_loop *loop, struct ev_io *watcher, int revents);

int new_tcp_server(const char *host, short port);
int set_nonblock(int fd);
int set_reuse_socket(int sock);
int set_address (const char *host, short port, struct sockaddr_in *addr);


int main(int argc , char *argv[])
{
	struct ev_loop *loop = ev_default_loop(0);

	int port = PORT_NO;
	if(argc==2){
		port = atoi(argv[1]);
	}else if(argc > 2){
		fprintf(stderr, "usage: server_libev [port]\n");
        return 1;
	}

	int fd = new_tcp_server("0.0.0.0", port);

	printf("Starting tcp server on :%d\n", port);

	ev_io listen_watcher;
	ev_io_init(&listen_watcher, on_accept, fd, EV_READ);
	ev_io_start(loop, &listen_watcher);

	ev_loop(loop, 0);

	return 0;
}



int new_tcp_server(const char *host, short port) {
	int fd;
	struct sockaddr_in address;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1) {
		perror("socket");
		return -1;
	}

	set_reuse_socket(fd);
	set_nonblock(fd);

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
	addr->sin_port = htons(port );
	return 0;
}

int set_nonblock(int fd) {
	return fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int set_reuse_socket(int fd) {
	int ok = 1;
	return setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &ok, sizeof(ok));
}

void on_accept(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	struct ev_io *client_watcher = (struct ev_io*)malloc(sizeof(struct ev_io));

	if(EV_ERROR & revents) {
		perror("invalid event");
		return;
	}

	int client_fd = accept(watcher->fd, (struct sockaddr*)&client_addr, &client_len);

	if (client_fd < 0) {
		perror("accept");
		return;
	}

	set_nonblock(client_fd);

	total_clients++;

	ev_io_init(client_watcher, on_read, client_fd, EV_READ);
	ev_io_start(loop, client_watcher);
}


void on_read(struct ev_loop *loop, struct ev_io *watcher, int revents)
{
	char buffer[BUFFER_SIZE];
	ssize_t len;

	if(EV_ERROR & revents) {
		return;
	}

	len = recv(watcher->fd, buffer, BUFFER_SIZE, 0);

	if (len < 0) {
		return;
	} else if (len == 0) {
		// disconnected
		ev_io_stop(loop, watcher);
		close(watcher->fd);
		free(watcher);
		total_clients--;
		return;
	}

	ssize_t sent = send(watcher->fd, buffer, len, 0);

	if (sent != len) {
		perror("send");
	}

	memset(buffer, 0, BUFFER_SIZE);
}
