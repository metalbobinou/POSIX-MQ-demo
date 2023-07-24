#include "pre_work_ex2.h"

/*
** Prepare the environment by deleting old MQ, and creating a new one.
*/
int			pre_work(void)
{
  mqd_t			MQ;
  int			res;

  res = unlink_mq();
  res = create_queue(&MQ);
  if (res == -1)
    return (-1);
  close_mq(&MQ);
  printf("MQueue of 10 messages MAX created !");
  return (0);
}
