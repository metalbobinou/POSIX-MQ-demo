#ifndef SENDER_EX2_H_
# define SENDER_EX2_H_

# include <unistd.h>
# include <mqueue.h>
# include <fcntl.h>     /* For O_* constants */
# include <sys/stat.h>  /* For mode constants */

# include <signal.h>
# include <sys/types.h>

# include "ansi.h"
# include "mq_lib.h"
# include "pre_work_ex2.h"

/*
** Open the queue, write many things inside, then quit it.
** Everything that is wrote, is also copy to the file "filename".
*/
int	timed_write_mq(char	*filename);

#endif /* !SENDER_EX2_H_ */
