#ifndef MQ_EXAMPLE_H_
# define MQ_EXAMPLE_H_

# include <unistd.h>
# include <mqueue.h>
# include <fcntl.h>     /* For O_* constants */
# include <sys/stat.h>  /* For mode constants */

# include "ansi.h"
# include "mq_lib.h"

/*
** Create and set attribute to the queue, then quit it.
*/
int	pre_work(void);

/*
** Open the queue, write many things inside, then quit it.
** Everything that is wrote, is also copy to the file "filename".
*/
int	parent_mq(char	*filename);

/*
** Open the queue, read things inside, then quit it.
** Everything that is read, is also copy to the file "filename".
*/
int	child_mq(char	*filename);

#endif /* !MQ_EXAMPLE_H_ */
