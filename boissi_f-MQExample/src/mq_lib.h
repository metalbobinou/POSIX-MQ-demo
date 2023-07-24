#ifndef MQ_LIB_H_
# define MQ_LIB_H_

# include <unistd.h>
# include <mqueue.h>
# include <fcntl.h>     /* For O_* constants */
# include <sys/stat.h>  /* For mode constants */
# include <limits.h>

# include "ansi.h"

/*
** Create the queue my_MQ with attributes, and close it.
** Return 0 if the creation succeed, -1 if fail.
*/
int	create_queue(mqd_t		*my_MQ);

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

#endif /* !MQ_LIB_H_ */
