#include "mq_example1.h"

int	simple_example(void)
{
  int	pid, res = 0;

  if (pre_work_non_block() == -1)
    return (-1);
  pid = fork();
  switch (pid)
  {
    case (-1) :
      /* Fail Fork */
      perror("Fork failed.\n");
      res = -1;
      break ;
    case (0) :
      /* Child Process */
      res = child_mq("child.log");
      break;
    default :
      /* Parent Process */
      res = parent_mq("parent.log");
      break;
  }
  return (res);
}
