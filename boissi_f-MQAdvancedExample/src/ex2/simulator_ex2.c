#include "simulator_ex2.h"

/*
** Simulate a complete MQ exchange.
** This function mainly read, and sometimes calls for writing and put notifies.
*/
int			timed_simu_mq(char	*filename_recv,
				      char	*filename_send)
{
  mqd_t				MQ;
  FILE				*fd;
  int				res;
  char				*buf;
  unsigned			priority;
  int				i = 0;
  /* Notify variables */
  union sigval			sigvalue;
  int				signo = SIGUSR1;
  /* pthread_attr_t		attr; */

  fd = fopen(filename_recv, "w");
  if (fd == NULL)
  {
    perror("Error : Child fopen failed !\n");
    return (-1);
  }

  buf = malloc(MY_BUF_LEN * sizeof (char));
  memset(buf, 0, MY_BUF_LEN * sizeof (char));

  if (open_mq(&MQ, O_RDONLY) == -1)
    return (-1);

  /* NONE Test */
  printf("\n\nWrite 10 messages in the queue.\n");
  timed_write_mq(filename_send);
  printf("Preparing a NONE notify for MQ...\n");
  res = notify_none(&MQ);
  if (res == -1)
  {
    perror("Error on notify NONE\n");
    return (-1);
  }
  printf("Begin reading 11 messages ! (Test timeout ~3 seconds)\n");
  for (i = 0; i != 11; i++)
    res = timed_recv(fd, &MQ, buf, MY_BUF_LEN, &priority);
  printf("End read.\n");
  printf("Write 10 messages in the queue.\n");
  printf("-- Nothing should happen now, because notify NONE. --\n");
  timed_write_mq(filename_send);

  /* SIGNAL Test */
  printf("\nPreparing a SIGNAL notify for MQ...\n");
  sigvalue.sival_int = 1337;
  signo = SIGUSR1; /* Repeat to not forget */
  catch_signal(signo);
  res = notify_signal(&MQ, sigvalue, signo);
  if (res == -1)
  {
    perror("Error on notify SIGNAL\n");
    return (-1);
  }
  printf("Begin reading 11 !\n");
  for (i = 0; i != 11; i++)
    res = timed_recv(fd, &MQ, buf, MY_BUF_LEN, &priority);
  printf("End read.\n");
  printf("Write 10 messages in the queue.\n");
  printf("-- A signal should appear JUST after this message,"
	 " and ONLY there. --\n");
  timed_write_mq(filename_send);

  /* THREAD Test */
  printf("\nPreparing a THREAD notify for MQ...\n");
  sigvalue.sival_int = 42;
  res = notify_thread(&MQ, sigvalue, my_thread_handler, /* &attr */ NULL);
  if (res == -1)
  {
    perror("Error on notify THREAD\n");
    return (-1);
  }
  printf("Begin reading 11 !\n");
  for (i = 0; i != 11; i++)
    res = timed_recv(fd, &MQ, buf, MY_BUF_LEN, &priority);
  printf("End read.\n");
  printf("Write 10 messages in the queue.\n");
  printf("-- A thread should appear JUST after this message,"
	 " and ONLY there. --\n");
  timed_write_mq(filename_send);

  printf("\nEnd of the example 2.\n");
  res = res;

  close_mq(&MQ);
  free(buf);
  fclose(fd);
  unlink_mq();
  return (0);
}
