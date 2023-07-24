#ifndef MQ_LIB_H_
# define MQ_LIB_H_

# include <unistd.h>
# include <mqueue.h>
# include <fcntl.h>     /* For O_* constants */
# include <sys/stat.h>  /* For mode constants */
# include <limits.h>
# include <signal.h>
# include <time.h>

# include "ansi.h"

/*
** Create the queue my_MQ with attributes, and close it.
** Return 0 if the creation succeed, -1 if fail.
*/
int	create_queue(mqd_t		*my_MQ);

/*
** Create the queue my_MQ with attributes + O_NONBLOCK, and close it.
** Return 0 if the creation succeed, -1 if fail.
*/
int	create_queue_non_block(mqd_t	*my_MQ);

/*
** Open the queue my_MQ with the oflag.
** Return 0 if the open succeed, -1 if fail.
*/
int	open_mq(mqd_t			*my_MQ,
		int			oflag);

/*
** Close the my_MQ queue.
*/
void	close_mq(mqd_t			*my_MQ);

/*
** Delete the queue from the FS.
*/
int	unlink_mq(void);

/*
** Write once "len" bytes from "str" in my_MQ with priority.
** Return 0 if write succeed, -1 if the message is too long, or the number of
** retries before sending.
*/
int	write_in_queue(mqd_t		*my_MQ,
		       char		*str,
		       size_t		len,
		       unsigned		priority);

/*
** Read a message and put the content in buf[len] from my_MQ with priority.
** Return -1 if read failed, or the number of bytes read.
*/
int	read_from_queue(mqd_t		*my_MQ,
			char		*buf,
			size_t		len,
			unsigned	*priority);

/*
** Print the attributes of the queue my_MQ.
** Return -1 if mq_getattr failed.
*/
int	print_attr_queue(mqd_t		*my_MQ);

/*
** Set attributes to the queue my_MQ.
** Return -1 if mq_setattr failed, and print some details.
*/
int	setattr_mq(mqd_t		*my_MQ,
		   long			flags);

/*
** Send "len" characters from the buffer "str" into the queue my_MQ, with the
** priority "priority".
** If O_NONBLOCK is not set, and the queue is full, it waits for nearly 3
** seconds before cancelling.
** If O_NONBLOCK is set, it runs like send_mq().
** If "len" is superior to the maximum of the queue, nothing is done, and it
** returns -1.
** It also return -1 when mq_send() fails, or 0 if everything went well.
*/
int	timedsend_mq(mqd_t		*my_MQ,
		     char		*str,
		     size_t		len,
		     unsigned		priority);

/*
** Receive a message from the queue "my_MQ" and put it in the buffer "str" of
** lenght "len".
** Priority should be a reference, because it is modified to the priority that
** the message was sent with.
** The oldest with higher priority message is extracted first.
** If the queue has no O_NONBLOCK flags, and is empty, it will wait for 3
** seconds before failing.
** If O_NONBLOCK is set, this function works like receive_mq().
** If the buffer is too small, it is reallocated with realloc.
** The function returns the number of characters read, or -1 if it fails.
*/
int	timedreceive_mq(mqd_t		*my_MQ,
			char		*str,
			size_t		len,
			unsigned	*priority);

/*
** Put a SIGEV_NONE notify on the queue my_MQ.
** There is no use for this function, except preventing another processus from
** putting a notification too.
** It returns 0 on success, and -1 if fail.
*/
int	notify_none(mqd_t		*my_MQ);

/*
** Put a SIGEV_SIGNAL notify on the queue my_MQ.
** When the queue is empty, a signal 42 is sent to the processus, and some
** informations can be read.
** Those informations are sent by a sigevent structure.
** Sigvalue is a value that will be sent when the signal will be create.
** Signo is the signal you want to receive when the MQ will be empty.
** It return 0 on success, or -1 if it fails.
*/
int	notify_signal(mqd_t		*my_MQ,
		      union sigval	sigvalue,
		      int		signo);

/*
** Put a SIGEV_THREAD notify on the queue my_MQ.
** When the queue is empty, a thread is launched with the function given to it.
** Sigvalue is a value that will be receive by the thread.
** Handler is the function that will be called when the MQ will be empty.
** Attr are the thread attributes, may be NULL if you are not sure.
** It returns 0 on success or -1 if it fails.
*/
int	notify_thread(mqd_t		*my_MQ,
		      union sigval	sigvalue,
		      void		(*handler)(),
		      pthread_attr_t	*attr);

#endif /* !MQ_LIB_H_ */
