#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int ssock,csock;      // creating server and clinet socket discriptor
	unsigned int len;
	struct sockaddr_in server,client;   // creating server & client socket object

	if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{     
		// creating socket
		perror("socket: ");
		exit(-1);
	}

	server.sin_family=AF_INET;
	server.sin_port=htons(10005);       // initializing server socket parameters..
	server.sin_addr.s_addr=INADDR_ANY;   //inet_addr("127.0.0.1");
	bzero(&server.sin_zero,0);		//appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.. 
	
	len=sizeof(struct sockaddr_in);
	if((bind(ssock,(struct sockaddr *)&server,len))==-1)
	{ // binding port & IP  
		perror("bind error: ");
		exit(-1);
	}

	if((listen(ssock,5))==-1)
	{     
	// listening for client
		perror("listen error: ");                     
		exit(-1);
	}
	if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1)
	{  // accepting connectn
		perror("accept error: ");                         
		exit(-1);
	}
	ifstream infile;
    infile.open("book.txt");
    string line;
	int f=-1,g=-2;
    while(getline(infile,line))
    {
		//char buffer[512];
        //strcpy(buffer,line.c_str());
        //send(csock,buffer,sizeof(buffer),0);
		//send(csock,line.c_str(),sizeof(char)*line.length(),0);
		stringstream s(line);
		string a;
		while(getline(s,a,' '))
		{
			int b=stoi(a);
			b*=2;
			send(csock,&b,sizeof(b),0);
		}
		send(csock,&f,sizeof(f),0);
    }
    send(csock,&g,sizeof(g),0);
    infile.close();
	close(ssock);
}