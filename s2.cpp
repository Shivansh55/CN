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
	server.sin_port=htons(10000);       // initializing server socket parameters..
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
	while(1)
	{
        int f=0;
        char word[512];
        char mean[512];
		recv(csock,&word,sizeof(word),0);
		ifstream infile;
        infile.open("words.txt");
        string line;
        while(getline(infile,line))
        {
            char a[512];char b[512];
            sscanf(line.c_str(),"%s %s",a,b);
            if(strcmp(a,word)==0)
            {
                strcpy(mean,b);
                f=1;
                break;
            }
        }
        infile.close();
        if(f==1)
        {
            cout<<mean<<endl;
            send(csock,&mean,sizeof(mean),0);
        }
        else
        {
            cout<<"Meaning Not Found"<<endl;
            send(csock,&"no",sizeof("no"),0);
            recv(csock,&mean,sizeof(mean),0);
            ofstream outfile;
            outfile.open("words.txt",std::ios_base::app);
            string a=word,b=mean;
            outfile<<a<<" "<<b<<endl;
            outfile.close();
        }
	}
	close(ssock);
}
