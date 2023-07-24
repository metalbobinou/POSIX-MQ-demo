#include "receiver_ex2.h"

/*
** A function that read from the MQ and write this into a file.
** MQ is read with a timer maximum.
*/
static int	timed_read(FILE		*fd,
			   mqd_t	*MQ,
			   char		*buf,
			   size_t	len,
			   unsigned	*priority)
{
  time_t	sec;
  int		res;

  sec = time(NULL);
  res = timedreceive_mq(MQ, buf, len, priority);
  if ((res > (int) len) || (res == -1))
    return (-1);

  res = fwrite(buf, sizeof (char), res, fd);
  if ((size_t) res > len)
  {
    perror("Error : Child fwrite failed !\n");
    return (-1);
  }
  fprintf(fd, " -- pri : %u (timestamp : %u)\n",
	  (unsigned int) (*priority),
	  (unsigned int) sec);
  return (res);
}

/*
** A function that tries 1 time to read a message in the MQ.
*/
int		timed_recv(FILE		*fd,
			   mqd_t	*MQ,
			   char		*buf,
			   int		len,
			   unsigned	*priority)
{
  int		res, max = 0;

  res = timed_read(fd, MQ, buf, len, priority);
  while ((res < 0) && (max != 1))
  {
    printf("Trying again ! res : %d max : %d\n", res, max);
    res = timed_read(fd, MQ, buf, len, priority);
    sleep(1);
    max++;
  }
  return (res);
}
