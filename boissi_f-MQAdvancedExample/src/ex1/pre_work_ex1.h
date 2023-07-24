#ifndef PRE_WORK_EX1_H_
# define PRE_WORK_EX1_H_

# include <unistd.h>
# include <mqueue.h>
# include <fcntl.h>     /* For O_* constants */
# include <sys/stat.h>  /* For mode constants */

# include "ansi.h"
# include "mq_lib.h"

# define MY_BUF_LEN	1024

/*
** Create and set attribute to the queue + O_NONBLOCK, then quit it.
*/
int	pre_work_non_block(void);

#endif /* !PRE_WORK_EX1_H_ */
