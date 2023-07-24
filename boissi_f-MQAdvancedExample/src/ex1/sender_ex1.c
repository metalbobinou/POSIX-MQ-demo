#include "sender_ex1.h"

int		parent_write(FILE	*fd,
			     mqd_t	*MQ,
			     char	*str,
			     size_t	len,
			     unsigned	priority)
{
  time_t	sec;
  int		res;

  res = fwrite(str, sizeof (*str), len, fd);
  if ((size_t) res < len)
  {
    perror("Error : Parent fwrite failed !\n");
    return (-1);
  }
  sec = time(NULL);
  res = write_in_queue(MQ, str, len, priority);
  fprintf(fd, " -- pri : %u (timestamp : %u)\n",
	  (unsigned int) priority,
	  (unsigned int) sec);
  return (res);
}

int		dup_n_send(FILE		*fd,
			   mqd_t	*MQ,
			   char		*str,
			   unsigned	priority)
{
  char		*tmp;
  int		res;

  tmp = strdup(str);
  res = parent_write(fd, MQ, tmp, strlen(tmp), priority);
  free(tmp);

  return (res);
}

int		parent_mq(char		*filename)
{
  mqd_t		MQ;
  FILE		*fd;
  int		res;

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
