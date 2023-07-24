#include "mq_example2.h"

int	complex_example(void)
{
  int	res = 0;

  if (pre_work() == -1)
    return (-1);
  res = timed_simu_mq("read.log", "write.log");

  return (res);
}
