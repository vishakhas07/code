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

int main()
{
    
	int sockfd, ret ;
	struct sockaddr_in sAddr, newAddr;
	socklen_t addr_size, newSockfd;

	char buff[1024];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0)

	{

		perror("socket() error");

		exit(1);

	}


	
	cout<<"[+]Server socket is created.\n";

	memset(&sAddr,'\0',sizeof(sAddr));
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(4056);
	sAddr.sin_addr.s_addr = inet_addr("127.0.0.1");


	
	ret = bind(sockfd,(struct sockaddr*)&sAddr,sizeof(sAddr));


	
	if(ret < 0)

	{

		perror("bind() error");

		exit(1);

	}


	
	cout<<"[+]Bind to the port: "<<4055<<endl;
	if(listen(sockfd,10) == 0)
            {
		cout<<"[+]Listening......."<<endl;
	        system("cls");
             }


	else

		cout<<"[-]Error in binding"<<endl;

	while(1){

		memset(&buff,'\0',sizeof(buff));

		newSockfd = accept(sockfd,(struct sockaddr*) &newAddr, &addr_size);

		if(newSockfd < 0)

		{

			perror("accept() error");

			exit(1);

		}

		if(fork() == 0){

			while(1){
                                
				read(newSockfd, buff, 1024);

				if(strcmp(buff,":Bye") == 0)

				{

					cout<<"Disconnected Client"<<endl;

					break;

				} 

				else

				{
					cout<<"Client Message: "<<buff<<endl;
					write(newSockfd, buff, strlen(buff));
                                          
					bzero(buff, sizeof(buff));	


				}

			}

		}

		else

		{
			close(sockfd);
				wait(0);
						}
				
			}

		close(newSockfd);

			return 0;
}
