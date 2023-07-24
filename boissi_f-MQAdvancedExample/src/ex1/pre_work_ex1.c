#include "pre_work_ex1.h"

int	pre_work_non_block(void)
{
  mqd_t	MQ;
  int	res;

  res = create_queue_non_block(&MQ);
  if (res == -1)
    return (-1);
  close_mq(&MQ);
  return (0);
}
