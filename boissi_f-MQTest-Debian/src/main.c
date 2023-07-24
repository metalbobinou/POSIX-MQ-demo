#include "main.h"

#define MQ_NAME "/queuetest"
#define BUF_LEN 512

int			main(void)
{
  struct mq_attr	attr;
  ssize_t		len_recv;
  mqd_t			My_MQ;
  char			*text;
  char			recv[BUF_LEN];

  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = BUF_LEN;
  attr.mq_curmsgs = 0;

  My_MQ = mq_open(MQ_NAME, O_RDWR | O_CREAT, 0644, &attr);
  if ((int) My_MQ == -1)
  {
    perror("Error : mq_open failed !\n");
    return (-1);
  }

  printf("%s\n", "Envoi msg de priorite 42");
  text = strdup("Message test prio : 42 !");
  mq_send(My_MQ, text, strlen(text), 42);
  free(text);

  printf("%s\n", "Envoi msg de priorite 21");
  text = strdup("Message test prio : 21 !");
  mq_send(My_MQ, text, strlen(text), 21);
  free(text);

  memset(recv, 0, BUF_LEN);
  len_recv = mq_receive(My_MQ, recv, BUF_LEN, NULL);
  printf("Premier msg recu (len : %u) : %s\n", (unsigned int) len_recv, recv);

  memset(recv, 0, BUF_LEN);
  len_recv = mq_receive(My_MQ, recv, BUF_LEN, NULL);
  printf("Deuxieme msg recu (len : %u) : %s\n", (unsigned int) len_recv, recv);

  mq_close(My_MQ);
  mq_unlink(MQ_NAME);
  return (0);
}
