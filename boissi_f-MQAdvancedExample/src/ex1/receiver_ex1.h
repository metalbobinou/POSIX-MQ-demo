#ifndef RECEIVER_EX1_H_
# define RECEIVER_EX1_H_

# include <unistd.h>
# include <mqueue.h>
# include <fcntl.h>     /* For O_* constants */
# include <sys/stat.h>  /* For mode constants */

# include "ansi.h"
# include "mq_lib.h"
# include "pre_work_ex1.h"

/*
** Open the queue, read things inside, then quit it.
** Everything that is read, is also copy to the file "filename".
*/
int	child_mq(char	*filename);

#endif /* !RECEIVER_EX1_H_ */
