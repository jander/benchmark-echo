#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> //inet_addr
#include <pthread.h>
#include <time.h>

#define BUFFER_SIZE 10240

int new_tcp_client(const char *host, short port);
int set_address (const char *host, short port, struct sockaddr_in *addr);
char * read_from_file(const char* filename);

void* do_connect();

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

int nsuccess;		// 成功的次数
int nconn = 1;		// 每个线程的连接次数
int necho = 1;		// 每次连接的echo次数
int nthread = 1;	// 线程数量

const char* host;	// 服务器 ip
short port;			// 服务器 port

// 发送的字符串
char* message;
const char* filename; // load file text to send;


int main (int argc , char *argv[]) {
	int opt;

    while (-1 != (opt = getopt(argc, argv, "t:c:e:p:f:"))) {
        switch (opt) {
        case 'e':
            necho = atoi(optarg);
            break;
        case 'c':
        	nconn = atoi(optarg);
        case 't':
            nthread = atoi(optarg);
            break;
        case 'p':
            port = (short) atoi(optarg);
            break;
        case 'f':
        	filename = optarg;
        	break;
        default:
            fprintf(stderr, "Unknown option: %c\n", opt);
            return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "usage: client [-e echo counts per conn] [-c conn count per threads]  [-t threads count] [-p port] [-f filename to load]serverip\n");
        return 2;
    }

    host = argv[optind];

    if (filename != NULL){
    	message = read_from_file(filename);
    }else{
    	message = "hello world\n";
    }

    pthread_mutex_lock(&g_mutex);

    long long total_time;
    struct timespec t1, t2;
    int err;

	pthread_t *threads = malloc(sizeof(pthread_t)*nthread);

	for (int i = 0; i < nthread; ++i) {
		err = pthread_create(&threads[i], NULL, (void*)do_connect, NULL);
		if (err != 0) {
		    perror("create thread");
		    return 3;
		}
	}
	pthread_mutex_unlock(&g_mutex);

	clock_gettime(CLOCK_MONOTONIC, &t1);

	for (int i = 0; i < nthread; ++i) {
		err = pthread_join(threads[i], NULL);
		if (err != 0) {
			perror("join a thread.");
			return 4;
		}
	}

	clock_gettime(CLOCK_MONOTONIC, &t2);

	total_time  = t2.tv_sec * 1000000000LL + t2.tv_nsec;
	total_time -= t1.tv_sec * 1000000000LL + t1.tv_nsec;
	
	free(threads);
	free(message);
    printf("Throughput: %.2lf [reqests/sec], errors: %d\n",
            (nsuccess)*1000000000.0/(total_time), nthread*nconn*necho-nsuccess);

	return 0;
}


char * read_from_file(const char* filename)
{
	char * buffer;

	FILE *f=fopen(filename,"rb");
	fseek(f,0,SEEK_END);
	long fsize=ftell(f);
	fseek(f,0,SEEK_SET);
	buffer = (char*)malloc(fsize+1);
	long ret = fread(buffer, 1, fsize, f);
	if (ret != fsize){
		exit(1);
	}
	buffer[fsize] = '\0';
	fclose(f);

	return buffer;
}


void* do_connect()
{
	char buffer[BUFFER_SIZE];

	for (int i=0; i<nconn; i++){

		int fd = new_tcp_client(host, port);

		for (int i=0; i<necho; i++) {
			if (write(fd, message, strlen(message)) < 0) {
				perror("Send failed");
				close(fd);
				continue;
			}

			memset(buffer, 0, BUFFER_SIZE);

			if (read(fd, buffer, BUFFER_SIZE -1) < 0){
				perror("recv failed");
				close(fd);
				continue;
			}

			if(strcmp(message, buffer) == 0){
				pthread_mutex_lock(&g_mutex);
				nsuccess ++;
				pthread_mutex_unlock(&g_mutex);
			}
		}

		close(fd);
	}
	pthread_exit(NULL);
}


int new_tcp_client(const char *host, short port)
{
	int fd;
	struct sockaddr_in address;

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd == -1) {
		perror("socket");
		return -1;
	}

	set_address(host, port, &address);

	if (connect(fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
		perror("connect");
		close(fd);
		return -1;
	}

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

