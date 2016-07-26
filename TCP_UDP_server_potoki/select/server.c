#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h> 
#include <string.h>

int socktcp;	// TCP сокет 
int sockudp;	// UDP сокет

int main ()
{
	char mess[64];		// полученное сообщение
	struct sockaddr_in addr;	// структура с адресом TCP
	struct sockaddr_in servaddr, clilen; // Структуры для адресов сервера и клиента UDP
	fd_set rset;	// Отслеживаемые дескрипторы

	//задаем параметры сервера
    addr.sin_family = AF_INET;
 	addr.sin_port = htons(3428);
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    socktcp = socket(AF_INET, SOCK_STREAM, 0);	//создаем сокет для входных подключений TCP
	if(socktcp < 0)
    {
        perror("socket");
        exit(1);
    }

    if(bind(socktcp, (struct sockaddr *)&addr, sizeof(addr)) < 0) // связываемся с сетевым устройство. 
    //Сейчас это устройство lo - "петля", которое используется для отладки сетевых приложений
    {
        perror("bind");
        exit(2);
    }

    listen(socktcp, 1); // очередь входных подключений 

    if((sockudp = socket(AF_INET, SOCK_DGRAM, 0)) < 0)	// Создаем UDP сокет
    {
        perror("socket"); 
        exit(1);  
    }

    if(bind(sockudp, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){	// Настраиваем адрес сокета 
        perror("bind");
        close(sockudp);
        exit(1);
    }
    // int select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
    

}