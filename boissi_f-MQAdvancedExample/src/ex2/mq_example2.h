#ifndef MQ_EXAMPLE2_H_
# define MQ_EXAMPLE2_H_

# include <unistd.h>
# include <mqueue.h>
# include <fcntl.h>     /* For O_* constants */
# include <sys/stat.h>  /* For mode constants */

# include <signal.h>
# include <sys/types.h>

# include "ansi.h"
# include "mq_lib.h"
# include "pre_work_ex2.h"
# include "simulator_ex2.h"

/*
** Launch the complex simulation with MQ_NOTIFY, etc...
*/
int	complex_example(void);

#endif /* !MQ_EXAMPLE2_H_ */
