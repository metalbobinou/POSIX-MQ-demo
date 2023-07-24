#ifndef SIMULATOR_EX2_H_
# define SIMULATOR_EX2_H_

# include <unistd.h>
# include <mqueue.h>
# include <fcntl.h>     /* For O_* constants */
# include <sys/stat.h>  /* For mode constants */

# include <signal.h>
# include <sys/types.h>

# include "ansi.h"
# include "mq_lib.h"
# include "pre_work_ex2.h"
# include "sender_ex2.h"
# include "receiver_ex2.h"
# include "notify_signal_ex2.h"
# include "notify_thread_ex2.h"

/*
** Open the queue, read and write things inside, then quit it.
** Everything that is read, is also copy to the file "filename_recv".
** It is the complete simulation.
*/
int	timed_simu_mq(char	*filename_recv,
		      char	*filename_send);

#endif /* !SIMULATOR_EX2_H_ */
