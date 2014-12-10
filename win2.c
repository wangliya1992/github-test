#include <stdio.h>
#include <winsock2.h>
#pragma coment ( lib , "ws2_32" ) 

void server_socket( char * , int ) ;
void client_socket( char * , int ) ;
int main(){
	printf("OK\n") ;
	char * ip = "127.0.0.1" ;
	int port = 8835 ;
	server_socket( ip , port ) ;
	return  0 ;
}

void server_socket( char * ip , int port ){
	WSADATA wsadata ;
	if( WSAStartup( MAKEWORD( 2 , 2 ) , &wsadata ) != 0 ){
		printf("Fail WSAStartup !\n") ;
	}else{
		printf("WSAStartup success !\n") ;
	}

	SOCKET server_sock = socket( AF_INET , SOCK_STREAM , 0 ) ;

	sockaddr_in sockaddr ;
	sockaddr.sin_family = AF_INET ;
	sockaddr.sin_addr.S_un.S_addr = inet_addr( "127.0.0.1" ) ;
	sockaddr.sin_port = port ;

	bind( server_sock , (SOCKADDR*)&sockaddr , sizeof( SOCKADDR ) ) ;
	
	listen( server_sock , 10 ) ;

	while( true ){
		SOCKADDR sockaddr ;
		int size = sizeof( SOCKADDR ) ;
		printf("Start accept ... \n") ;
		SOCKET client = accept( server_sock , &sockaddr , &size ) ;
		printf("Aready accept\n") ;
		char recvs [MAXBYTE] = {0} ;
		recv( client , recvs , MAXBYTE , 0 ) ;
		printf("From client :%s\n" , recv) ;
		char *msg = "Server aready accept!\n" ;
		send( client , msg , sizeof(msg)+sizeof(char) , 0 ) ;
	}
	closesocket( server_sock ) ;
	WSACleanup() ;
	printf("Server exited !\n") ;
}
