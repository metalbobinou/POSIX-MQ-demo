#ifndef PRE_WORK_EX2_H_
# define PRE_WORK_EX2_H_

# include <unistd.h>
# include <mqueue.h>
# include <fcntl.h>     /* For O_* constants */
# include <sys/stat.h>  /* For mode constants */

# include <signal.h>
# include <sys/types.h>

# include "ansi.h"
# include "mq_lib.h"

# define	MY_BUF_LEN	1024

/*
** Create and set attribute to the queue, then quit it.
*/
int	pre_work(void);

#endif /* !PRE_WORK_EX2_H_ */
