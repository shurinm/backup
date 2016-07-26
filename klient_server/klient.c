#include <stdio.h>
#include <mqueue.h>
#include <string.h>

#define SIZE       256
 
int main(int argc, char **argv)
{
  mqd_t mqd;
  char new_text[SIZE];
  // Атрибуты очереди.
  struct mq_attr attr, old_attr;
  int prio;
  //Открываем "/my_queue" для отправки и приёма. 
  mqd = mq_open("/blblblbbl", O_CREAT | O_RDWR, 0666, NULL);
  /*
   * Теперь принимаем сообщение из очереди. Это блокирующий вызов.
   * Приоритет принятого сообщения сохраняется в prio. Функция
   * принимает самое старое из сообщений с наивысшим приоритетом
   * из очереди сообщений. Если размер буфера, указанный аргументом
   * msg_len, меньше, чем атрибут mq_msgsize очереди сообщений,
   * вызов функции не будет успешным и вернёт ошибку.
   */
  if (mq_receive(mqd, new_text, SIZE, &prio) == -1)
    perror("cannot receive");
    return -1;
 
  printf("Message: %s, prio = %d\n", new_text, prio);
 
 /* Закрываем очередь... */
  if (mq_close(mqd) == -1)
  perror("Closing queue error");
  //Отсоединяем очередь
  if (mq_unlink("/blblblbbl") == -1)
    perror("Removing queue error");
  return 0;
}