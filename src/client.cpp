#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h> /* for definition of errno */
#include <stdarg.h> /* ISO C variable aruments */
#include <cstring>
#define port 4005

using namespace std;

#define PORT 4056

int main()
{

	int sockfd, ret;
	struct sockaddr_in sAddr;
	char buff[1024];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0)

	{

		perror("socket() error");

		exit(1);

	}


	
	cout<<"[+]Client socket is created.\n";
	memset(&sAddr,'\0',sizeof(sAddr));
	sAddr.sin_family = AF_INET;

	sAddr.sin_port = htons(PORT);
	sAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ret = connect(sockfd, (struct sockaddr*)&sAddr, sizeof(sAddr));


	
	if(ret < 0)

	{

		perror("connect() error");

		exit(1);

	}

	cout<<"[+]Connected to the Server"<<endl;

	while(1)

	{

		cout<<"Client: \t";
		cin>>buff;

		write(sockfd, buff, strlen(buff));

		if(strcmp(buff, ":Bye") == 0)

		{

			close(sockfd);
			cout<<"Disconnected from the server"<<endl;
			exit(0);

		}

		bzero(buff, sizeof(buff));

		if(read(sockfd, buff, 1024) < 0)
					{

						perror("read() error");

						exit(1);

					}

		else

			cout<<"Server: \t"<<buff<<endl;

	}
	return 0;

}
