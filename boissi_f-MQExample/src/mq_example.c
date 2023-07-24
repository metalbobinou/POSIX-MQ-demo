#include "mq_example.h"

#define	MY_BUF_LEN	1024

int	pre_work(void)
{
  mqd_t	MQ;
  int	res;

  res = create_queue(&MQ);
  if (res == -1)
    return (-1);
  close_mq(&MQ);
  return (0);
}

int	parent_write(FILE		*fd,
		     mqd_t		*MQ,
		     char		*str,
		     size_t		len,
		     unsigned		priority)
{
  int	res;

  res = fwrite(str, sizeof (*str), len, fd);
  if ((size_t) res < len)
  {
    perror("Error : Parent fwrite failed !\n");
    return (-1);
  }
  res = write_in_queue(MQ, str, len, priority);
  fprintf(fd, " -- pri : %u\n", (unsigned int) priority);
  return (res);
}

int	dup_n_send(FILE			*fd,
		   mqd_t		*MQ,
		   char			*str,
		   unsigned		priority)
{
  char	*tmp;
  int	res;

  tmp = strdup(str);
  res = parent_write(fd, MQ, tmp, strlen(tmp), priority);
  free(tmp);

  return (res);
}

int	parent_mq(char			*filename)
{
  mqd_t	MQ;
  FILE	*fd;
  int	res;

  fd = fopen(filename, "w");
  if (fd == NULL)
  {
    perror("Error : Parent fopen failed !\n");
    return (-1);
  }

  if (open_mq(&MQ, O_WRONLY) == -1)
    return (-1);

  res = dup_n_send(fd, &MQ, "01 Message de prio 21.", 21);
  res = dup_n_send(fd, &MQ, "02 Message de prio 42 !", 42);
  res = dup_n_send(fd, &MQ, "03 Message de prio 84 !!!", 84);
  res = dup_n_send(fd, &MQ, "04 Message de prio 30", 30);
  res = dup_n_send(fd, &MQ, "05 Message de prio 10...", 10);
  res = dup_n_send(fd, &MQ, "06 1er Message normal", 0);
  res = dup_n_send(fd, &MQ, "07 2e Message normal", 0);
  res = dup_n_send(fd, &MQ, "08 3e Message normal", 0);
  res = dup_n_send(fd, &MQ, "09 Message de prio 84 (2) !!!", 84);
  res = dup_n_send(fd, &MQ, "10 4e Message normal", 0);
  res = dup_n_send(fd, &MQ, "11 5e Message normal", 0);
  res = dup_n_send(fd, &MQ, "12 6e Message normal", 0);
  res = dup_n_send(fd, &MQ, "13 7e Message normal", 0);
  res = dup_n_send(fd, &MQ, "14 8e Message normal", 0);
  res = res;

  close_mq(&MQ);

  fclose(fd);
  return (0);
}

int	child_read(FILE			*fd,
		   mqd_t		*MQ,
		   char			*buf,
		   size_t		len,
		   unsigned		*priority)
{
  int	res;

  res = read_from_queue(MQ, buf, len, priority);
  if ((res > (int) len) || (res == -1))
    return (-1);

  res = fwrite(buf, sizeof (char), res, fd);
  if ((size_t) res > len)
  {
    perror("Error : Child fwrite failed !\n");
    return (-1);
  }
  fprintf(fd, " -- pri : %u\n", (unsigned int) (*priority));
  return (res);
}

int	auto_recv(FILE			*fd,
		  mqd_t			*MQ,
		  char			*buf,
		  int			len,
		  unsigned		*priority)
{
  int	res, max = 0;

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

int	child_mq(char			*filename)
{
  mqd_t	MQ;
  FILE	*fd;
  int	res;
  char	*buf;
  unsigned	priority;
  int	i = 0;

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
