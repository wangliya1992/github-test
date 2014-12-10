#include <stdio.h>
#include <winsock2.h>
#pragma comment ( lib , "ws2_32" )

void client_socket( char *, int ) ;
int main(){
	char *ip = "127.0.0.1" ;
	int port = 8835 ;
	client_socket( ip , port ) ;
	return 0 ;
}
void client_socket( char *ip , int port ){
	WSADATA wsadata ;
	if( WSAStartup( MAKEWORD( 2 , 2 ) , &wsadata ) != 0 ){
		printf("Faild WSAStartup !\n") ;
	}else{
		printf("WSAStartup success !\n") ;
	}
	SOCKET client_sock = socket( AF_INET , SOCK_STREAM , 0 ) ;

	sockaddr_in sockaddr ;
	sockaddr.sin_family = AF_INET ;
	sockaddr.sin_addr.S_un.S_addr = inet_addr( "127.0.0.1" ) ;
	sockaddr.sin_port = port ;

	connect( client_sock , (SOCKADDR*)&sockaddr , sizeof(SOCKADDR) ) ;
	while(true){
		char msg [255];
		gets( msg ) ;
		send( client_sock , msg , sizeof(msg)+sizeof(char) , 0 ) ;
		char buf [MAXBYTE] = {0} ;
		recv( client_sock , buf , MAXBYTE , 0 ) ;
		printf( "From server:%s\n" , buf ) ;
	}
	
	
	closesocket( client_sock ) ;
	WSACleanup() ;
	printf("System exit !\n") ;

}
