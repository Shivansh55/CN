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

char func(char *msg,int num)
{
	int len=sizeof(msg)/sizeof(char);
	unordered_map<char,int> mp;
	for(int i=0;i<len;i++)
		mp[msg[i]]++;
	unordered_map<char,int>::iterator it;
	for(it=mp.begin();it!=mp.end();it++)
	{
		if(it->second==num)
			return it->first;
	}
	int max1=0;char ch;
	for(it=mp.begin();it!=mp.end();it++)
	{
		if(it->second>max1)
		{
			max1=it->second;
			ch=it->first;
		}
	}
	return ch;
}	
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
	server.sin_port=htons(10001);       // initializing server socket parameters..
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
	char pass[512];
	char msg[512];
	char Hi[512];
	recv(csock,&pass,sizeof(pass),0);
	if(strcmp(pass,"123456")==0)
	{
		cout<<"Correct Password"<<endl;
		recv(csock,&Hi,sizeof(Hi),0);
		cout<<"Hi received"<<endl;
		cout<<"Sending Hello"<<endl;
		send(csock,&"Hello",sizeof("Hello"),0);
		while(1)
		{
			char word[512];int num;
			recv(csock,&word,sizeof(word),0);
			recv(csock,&num,sizeof(num),0);
			cout<<word<<" "<<num<<endl;
			char ch=func(word,num);
			send(csock,&ch,sizeof(ch),0);           
	 		// sending data to client...	
			cout<<"Character sent = "<<ch<<endl;
		}
	}
	else
	{
		cout<<"Wrong Password"<<endl;
		send(csock,&"Wrong Password",sizeof("Wrong Password"),0);
	}
	close(ssock);
}
