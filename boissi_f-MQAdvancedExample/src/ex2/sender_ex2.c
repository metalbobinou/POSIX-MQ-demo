#include "sender_ex2.h"

/*
** A function that write in a file the message, before sending it in the MQ.
*/
int			timed_write(FILE	*fd,
				    mqd_t	*MQ,
				    char	*str,
				    size_t	len,
				    unsigned	priority)
{
  time_t		sec;
  int			res;

  res = fwrite(str, sizeof (*str), len, fd);
  if ((size_t) res < len)
  {
    perror("Error : Parent fwrite failed !\n");
    return (-1);
  }
  sec = time(NULL);
  res = timedsend_mq(MQ, str, len, priority);
  fprintf(fd, " -- pri : %u (timestamp : %u)\n",
	  (unsigned int) priority,
	  (unsigned int) sec);
  return (res);
}

/*
** Overlay that strdup the char*... nearly useless.
*/
int			timed_dup_n_send(FILE		*fd,
					 mqd_t		*MQ,
					 char		*str,
					 unsigned	priority)
{
  char			*tmp;
  int			res;

  tmp = strdup(str);
  res = timed_write(fd, MQ, tmp, strlen(tmp), priority);
  free(tmp);

  return (res);
}

/*
** The "writing" function : write 10 messages in the MQ.
*/
int			timed_write_mq(char	*filename)
{
  mqd_t			MQ;
  FILE			*fd;
  int			res;

  fd = fopen(filename, "w");
  if (fd == NULL)
  {
    perror("Error : Parent fopen failed !\n");
    return (-1);
  }

  if (open_mq(&MQ, O_WRONLY) == -1)
    return (-1);

  res = timed_dup_n_send(fd, &MQ, "01 Message de prio 21.", 21);
  res = timed_dup_n_send(fd, &MQ, "02 Message de prio 30 !", 30);
  res = timed_dup_n_send(fd, &MQ, "03 Message de prio 31 !!!", 31);
  res = timed_dup_n_send(fd, &MQ, "04 Message de prio 29", 29);
  res = timed_dup_n_send(fd, &MQ, "05 Message de prio 10...", 10);
  res = timed_dup_n_send(fd, &MQ, "06 1er Message normal", 0);
  res = timed_dup_n_send(fd, &MQ, "07 2e Message normal", 0);
  res = timed_dup_n_send(fd, &MQ, "08 3e Message normal", 0);
  res = timed_dup_n_send(fd, &MQ, "09 Message de prio 31 (2) !!!", 31);
  res = timed_dup_n_send(fd, &MQ, "10 4e Message normal", 0);
  res = res;

  close_mq(&MQ);

  fclose(fd);
  return (0);
}
