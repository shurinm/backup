#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

#define MSG_SIZE 		64
#define NICK_SIZE 		128
#define MAX_CLIENT 		64
#define MQ_MSG_NAME 	"/mq-msg-name"
#define MQ_CONN_NAME	"/mq-nick-name"

//Стуктура, описывающая клиента
struct client
{
	char nick[NICK_SIZE];
	mqd_t mq;
};

struct client clients[MAX_CLIENT];	//Массив клиентов
unsigned cnt_client;		//Количество клиентов
mqd_t mq_msg;				//Очередь для сообщений
mqd_t mq_conn;				//Очередь для авторизации (помещается ник)

void threads_connect( void *argv )
{
	char buf_conn[NICK_SIZE];

	while( 1 )
	{
		if( mq_receive( mq_conn, buf_conn, NICK_SIZE, 0 ) != -1 )
		{
			strcpy( clients[cnt_client].nick, buf_conn );
			clients[cnt_client].mq = mq_open( MQ_CONN_NAME, O_RDWR );
			if( clients[cnt_client].mq == -1 )
			{
				printf( "ERROR: connect [%s]\n", buf_conn );
				continue;
			}
			printf( "connect to server [%s]\n", buf_conn );
			cnt_client++;
		}
		else
			perror( "ERROR receive for connect" );
	}
}

void threads_resend( void *argv )
{
	char buf_msg[MSG_SIZE];

	while( 1 )
	{
		if( mq_receive( mq_msg, buf_msg, MSG_SIZE, 0 ) != -1 )
		{
			for( int i = 0; i < cnt_client; i++)
				if( mq_send( clients[i].mq, buf_msg, MSG_SIZE, 1 ) == -1 )
					perror( "ERROR send msg for client" );
		}
		else
			perror( "ERROR receive for resend" );
	}
}

//Создает очереди сервера
int create_mq( void )
{
	struct mq_attr attr;

	//Заполняем атрибуты
 	attr.mq_flags = 0;
    attr.mq_maxmsg = 15;
    attr.mq_msgsize = 255;
    attr.mq_curmsgs = 0;

	mq_msg = mq_open( MQ_MSG_NAME, O_CREAT | O_RDWR, 0777, &attr );
	mq_conn = mq_open( MQ_CONN_NAME, O_CREAT | O_RDWR, 0777, &attr );
	if( mq_conn == -1 || mq_msg == -1 )
		return -1;
	return 0;
}

//Удаляет очереди сервера
void destroy_mq( void )
{
	mq_unlink( MQ_MSG_NAME );
	mq_unlink( MQ_CONN_NAME );
}

int main (int argc, char **argv)
{
	pthread_t tid;
	void *retval;

	if( create_mq() == -1 )
	{
		printf( "ERROR: don't create mq.\n" );
		exit( -1 );
	}
  
	//Запуск потоков
	pthread_create( &tid, NULL, (void *)threads_connect, NULL );
	pthread_create( &tid, NULL, (void *)threads_resend, NULL );
	pthread_join( tid, &retval);

	destroy_mq();
	exit( 0 );
}
