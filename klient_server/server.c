#include <mqueue.h>
#include <stdio.h>
#include <string.h>

#define PRIORITY   1
#define SIZE       256

int main(int argc, char **argv)
{
	mqd_t mqd;
	char text[] = "Hello World";
	// Атрибуты очереди. 
	struct mq_attr queue_attr;
	queue_attr.mq_maxmsg = 32; // максимальное число сообщений в очереди в один момент времени 
  	queue_attr.mq_msgsize = SIZE; // максимальный размер очереди
  	//Открываем "/my_queue" для отправки и приёма. 
	mqd = mq_open("/blblblbbl", O_CREAT | O_WRONLY, 0666, NULL);
	if ( mqd == -1 ) {
		printf("Can't open the queue\n");
		return 1;
	}
	/*
   * Посылаем сообщение в очередь с приоритетом 1. Чем больше,
   * число, тем выше приоритет. Сообщение с высоким приоритетом
   * вставляется перед сообщением с низким приоритетом. Для
   * сообщений с одинаковым приоритетом работает принцип
   * первый вошёл, первый вышел.
   */
  if (mq_send(mqd, "ooo", 3, 12) == -1)
  	{
    	perror("Sending message error");
    	return -1;
  	}
  /* Закрываем очередь... */
  if (mq_close(mqd) == -1)
  perror("Closing queue error");
  return 0;
}