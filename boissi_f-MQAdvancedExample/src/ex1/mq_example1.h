#ifndef MQ_EXAMPLE1_H_
# define MQ_EXAMPLE1_H_

# include <unistd.h>
# include <mqueue.h>
# include <fcntl.h>     /* For O_* constants */
# include <sys/stat.h>  /* For mode constants */

# include "ansi.h"
# include "mq_lib.h"
# include "pre_work_ex1.h"
# include "sender_ex1.h"
# include "receiver_ex1.h"

/*
** Launch the simple example
*/
int	simple_example(void);

#endif /* !MQ_EXAMPLE1_H_ */
