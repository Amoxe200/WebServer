#include "common.h"
#include <string.h>

void err_n_die(const char *fmt, ...)
{
	int errno_save;
	va_list ap;

	//all system calls can set errno, so we need to save it now
	errno_save = errno;

	//print out the fmt+args to standard out 
	va_start(ap, fmt);
	vfprintf(stdout, fmt, ap);
	fprintf(stdout, "\n");
	fflush(stdout);

	//print out error message is errno was set.
	if (errno_save != 0)
	{
		fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
		fprintf(stdout, "\n");
		fflush(stdout);
	}
	va_end(ap);

	//this is the ..and_die part. Terminate with an error.
	exit(1);
}

char *bin2hex(const unsigned char *input, size_t len)
{
	char *result;
	char *hexits = "0123456789ABCDEF";

	if (input == NULL || len <= 0)
		return NULL;

	//(2 hexits+space)/chr + NULL
	int resultlength = (len *3)+1;

	result = malloc(resultlength);
	bzero(result, resultlength);

	for (int i=0; i < len; i++)
	{
		result[i * 3]	= hexits[input[i] >> 4];
		result[(i*3)+1] = hexits[input[i] & 0x0F];
		result[(i*3)+2] = ' '; // for readability
	}
	return result;
}

int main(int argc, char **argv)
{
	int			listenfd, connfd, n;
	struct sockaddr_in 	servaddr;
	uint8_t			buff[MAXLINE+1];
	uint8_t			recvline[MAXLINE+1];

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_n_die("socket error.");
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERVER_PORT);


	if ((bind(listenfd, (SA *) &servaddr, sizeof(servaddr))) < 0)
		err_n_die("bind error.");

	if ((listen(listenfd, 10)) < 0)
		err_n_die("listen error.");

	
	for( ; ; )
	{
		struct sockaddr_in 	addr;
		socklen_t addr_len;

		//accept blocks until an incoming connection arrives
		// it returns a "file descriptor" to the connection
		printf("waiting for a connection on port %d\n", SERVER_PORT);
		fflush(stdout);
		connfd = accept(listenfd, (SA *) NULL, NULL);


		// zero out the recieve buffer to make sure it ends up null terminated 
		memset(recvline, 0, MAXLINE);
		//Now read the client's message.
		while ( (n = read(connfd, recvline, MAXLINE-1) ) > 0)
		{
			fprintf(stdout, "\n%s\n\n%s", bin2hex(recvline, n), recvline);

			//hacky way to detect the end of the message.
			if (recvline[n-1] == '\n')
			{
				break;
			}
			memset(recvline, 0, MAXLINE);
		}
		if (n < 0)
			err_n_die("read erro");

		//now send a response.
		snprintf((char*)buff, sizeof(buff), "HTTP/1.0 200 OK\r\n\r\nHello");

		//note: normally, you may want to check the results from write and close
		//in case errors occur. For now, I'm ignoring them.
		write(connfd, (char*)buff, strlen((char *)buff));
		close(connfd);
	
	}
}

