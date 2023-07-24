#include "mq_lib.h"

#define	MQ_NAME	"/queuetest"
#define	BUF_LEN	512

unsigned int	g_mq_prio_max = 0;

int			create_queue(mqd_t		*my_MQ)
{
  struct mq_attr	attr;
  mqd_t			t_MQ;

# ifndef MQ_PRIO_MAX
  g_mq_prio_max = sysconf(_SC_MQ_PRIO_MAX);
# else
  g_mq_prio_max = MQ_PRIO_MAX;
#endif

  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = BUF_LEN;
  attr.mq_curmsgs = 0;

  t_MQ = mq_open(MQ_NAME, O_RDWR | O_CREAT, 0644, &attr);
  if (t_MQ == (mqd_t) -1)
  {
    perror("Error : mq_open failed !\n");
    return (-1);
  }
  (*my_MQ) = t_MQ;
  return (0);
}

int			create_queue_non_block(mqd_t	*my_MQ)
{
  struct mq_attr	attr;
  mqd_t			t_MQ;

# ifndef MQ_PRIO_MAX
  g_mq_prio_max = sysconf(_SC_MQ_PRIO_MAX);
# else
  g_mq_prio_max = MQ_PRIO_MAX;
#endif

  attr.mq_flags = 0;
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = BUF_LEN;
  attr.mq_curmsgs = 0;

  t_MQ = mq_open(MQ_NAME, O_RDWR | O_CREAT | O_NONBLOCK, 0644, &attr);
  if (t_MQ == (mqd_t) -1)
  {
    perror("Error : mq_open failed !\n");
    return (-1);
  }
  (*my_MQ) = t_MQ;
  return (0);
}

int			open_mq(mqd_t			*my_MQ,
				int			oflag)
{
  mqd_t			t_MQ;

  t_MQ = mq_open(MQ_NAME, oflag);
  if (t_MQ == (mqd_t) -1)
  {
    perror("Error : mq_open failed !\n");
    return (-1);
  }
  (*my_MQ) = t_MQ;
  return (0);
}

void			close_mq(mqd_t			*my_MQ)
{
  if (my_MQ != NULL)
    mq_close(*my_MQ);
}

int			unlink_mq(void)
{
  int			res;

  res = mq_unlink(MQ_NAME);
  if (res == -1)
    perror("mq_unlink failed ! Maybe the queue didn't exist before ?\n");
  return (res);
}

int			write_in_queue(mqd_t		*my_MQ,
				       char		*str,
				       size_t		len,
				       unsigned		priority)
{
  int			ret, state = 0;

  if (len == 0)
    len = BUF_LEN;
  if (len > BUF_LEN)
    return (-1);

  if (priority > (g_mq_prio_max - 1))
  {
    fprintf(stderr,
	    "/!\\ Priority (%u) of message exceeds MQ_PRIO_MAX (%u) ! /!\\\n",
	    priority,
	    g_mq_prio_max);
    priority = g_mq_prio_max - 1;
  }

  ret = mq_send((*my_MQ), str, len, priority);
  while (ret == -1) /* managing error */
  {
    perror("Retry sending\n");
    if (state == 10)
    {
      perror("Error : mq_send failed !\n");
      return (state);
    }
    ret = mq_send((*my_MQ), str, len, priority);
    /* usleep(100);*/
    sleep(1);
    state += 1;
  }
  return (state);
}

int			read_from_queue(mqd_t		*my_MQ,
					char		*str,
					size_t		len,
					unsigned	*priority)
{
  ssize_t		len_recv;
  char			buf[BUF_LEN];

  len_recv = mq_receive((*my_MQ), buf, BUF_LEN, priority);
  if ((int) len_recv == -1)
  {
    perror("Error : mq_receive failed !\n");
    return (-1);
  }
  if (len <= (size_t) len_recv)
    str = realloc(str, (len_recv + 1) * sizeof (char));
  str = strncpy(str, buf, len_recv);
  buf[len_recv] = '\0';
  return (len_recv);
}

int			print_attr_queue(mqd_t		*my_MQ)
{
  struct mq_attr	mq_stat;
  int			res;

  res = mq_getattr((*my_MQ), &mq_stat);
  if (res == -1)
  {
    perror("Error : mq_attr failed !\n");
    return (-1);
  }
  printf("Attribute of the Message Queue %s\n", MQ_NAME);
  printf("mq_flags : %ld\nmq_maxmsg : %ld\n"
	 "mq_msgsize : %ld\nmq_curmsgs : %ld\n\n",
	 mq_stat.mq_flags, mq_stat.mq_maxmsg,
	 mq_stat.mq_msgsize, mq_stat.mq_curmsgs);
  return (0);
}

int			setattr_mq(mqd_t		*my_MQ,
				   long			flags)
{
  struct mq_attr	mq_stat, old_stat;
  int			res;

  mq_stat.mq_flags = flags;
  res = mq_setattr((*my_MQ), &mq_stat, &old_stat);
  if (res == -1)
  {
    perror("Error : mq_setattr failed !\n");
    return (-1);
  }

  printf("Old attributes :\nold_flags : %ld\nold_maxmsg : %ld\n"
	 "old_msgsize : %ld\nold_curmsgs : %ld\nNew attributes :\n",
	 old_stat.mq_flags, old_stat.mq_maxmsg,
	 old_stat.mq_msgsize, old_stat.mq_curmsgs);
  print_attr_queue(my_MQ);
  return (0);
}

int			timedsend_mq(mqd_t		*my_MQ,
				     char		*str,
				     size_t		len,
				     unsigned		priority)
{
  struct timespec	time_s;
  time_t		secs;
  int			res;

  secs = time(NULL);
  time_s.tv_nsec = 0;
  time_s.tv_sec = secs + 3;

  if (len == 0)
    len = BUF_LEN;
  if (len > BUF_LEN)
    return (-1);

  if (priority > (g_mq_prio_max - 1))
  {
    fprintf(stderr, "Priority (%u) of message exceeds MQ_PRIO_MAX (%u) !",
	    priority, g_mq_prio_max);
    priority = g_mq_prio_max - 1;
  }

  res = mq_timedsend((*my_MQ), str, len, priority, &time_s);
  if (res == -1)
  {
    perror("Error : mq_timedsend failed !\n");
    return (-1);
  }
  return (res);
}

int			timedreceive_mq(mqd_t		*my_MQ,
					char		*str,
					size_t		len,
					unsigned	*priority)
{
  struct timespec	time_s;
  time_t		secs;
  ssize_t		len_recv;
  char			buf[BUF_LEN];

  secs = time(NULL);
  time_s.tv_nsec = 0;
  time_s.tv_sec = secs + 3;

  len_recv = mq_timedreceive((*my_MQ), buf, BUF_LEN, priority, &time_s);
  if ((int) len_recv == -1)
  {
    perror("Error : mq_timedreceive failed !\n");
    return (-1);
  }
  if (len <= (size_t) len_recv)
    str = realloc(str, (len_recv + 1) * sizeof (char));
  str = strncpy(str, buf, len_recv);
  buf[len_recv] = '\0';
  return (len_recv);
}

int			notify_none(mqd_t			*my_MQ)
{
  struct sigevent	sigev;
  int			res;

  sigev.sigev_notify = SIGEV_NONE;

  res = mq_notify((*my_MQ), &sigev);
  return (res);
}

int			notify_signal(mqd_t			*my_MQ,
				      union sigval		sigvalue,
				      int			signo)
{
/* union sigval		sigvalue; */
  struct sigevent	sigev;
  int			res;

/*  sigvalue.sival_int = 42; */ /* On remplie le sigvalue */

  sigev.sigev_notify = SIGEV_SIGNAL; /* alerte par signal/kill */
  sigev.sigev_value = sigvalue; /* union en int ou en void* */
  sigev.sigev_signo = signo; /* numero du signal a envoyer */

  res = mq_notify((*my_MQ), &sigev);
  return (res);
}

int			notify_thread(mqd_t			*my_MQ,
				      union sigval		sigvalue,
				      void			(*handler)(),
				      pthread_attr_t		*attr)
{
  struct sigevent	sigev;
  int			res;

  sigev.sigev_notify = SIGEV_THREAD; /* lancement d'un thread */
  sigev.sigev_value = sigvalue; /* union en int ou en void* */
  sigev.sigev_notify_function = handler; /* fonction a appeler */
  sigev.sigev_notify_attributes = attr; /* attributs du pthread */

  res = mq_notify((*my_MQ), &sigev);
  return (res);
}
