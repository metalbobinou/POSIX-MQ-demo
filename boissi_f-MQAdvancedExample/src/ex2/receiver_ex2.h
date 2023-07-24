#ifndef RECEIVER_EX2_H_
# define RECEIVER_EX2_H_

# include <unistd.h>
# include <mqueue.h>
# include <fcntl.h>     /* For O_* constants */
# include <sys/stat.h>  /* For mode constants */

# include "ansi.h"
# include "mq_lib.h"

/*
** A function that tries 3 times to read a message in the MQ.
*/
int		timed_recv(FILE		*fd,
			   mqd_t	*MQ,
			   char		*buf,
			   int		len,
			   unsigned	*priority);

#endif /* !RECEIVER_EX2_H_ */
