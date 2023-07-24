#include "receiver_ex1.h"

int		child_read(FILE		*fd,
			   mqd_t	*MQ,
			   char		*buf,
			   size_t	len,
			   unsigned	*priority)
{
  time_t	sec;
  int		res;

  sec = time(NULL);
  res = read_from_queue(MQ, buf, len, priority);
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

int		auto_recv(FILE		*fd,
			  mqd_t		*MQ,
			  char		*buf,
			  int		len,
			  unsigned	*priority)
{
  int		res, max = 0;

  res = child_read(fd, MQ, buf, len, priority);
  while ((res < 0) && (max != 10))
  {
    printf("Loopy ! res : %d max : %d\n", res, max);
    res = child_read(fd, MQ, buf, len, priority);
    sleep(1);
    max++;
  }
  return (res);
}

int		child_mq(char		*filename)
{
  mqd_t		MQ;
  FILE		*fd;
  int		res;
  char		*buf;
  unsigned	priority;
  int		i = 0;

  fd = fopen(filename, "w");
  if (fd == NULL)
  {
    perror("Error : Child fopen failed !\n");
    return (-1);
  }

  buf = malloc(MY_BUF_LEN * sizeof (char));
  memset(buf, 0, MY_BUF_LEN * sizeof (char));

  if (open_mq(&MQ, O_RDONLY) == -1)
    return (-1);

  for (i = 0; i != 14; i++)
    res = auto_recv(fd, &MQ, buf, MY_BUF_LEN, &priority);

  res = res;

  close_mq(&MQ);
  free(buf);
  fclose(fd);
  return (0);
}
