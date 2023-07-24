#ifndef NOTIFY_THREAD_EX2_H_
# define NOTIFY_THREAD_EX2_H_

# include <unistd.h>
# include <stdio.h>

/*
** A function called when a thread is created
** (when the MQ is empty with notify THREAD)
*/
void	my_thread_handler(void);

#endif /* !NOTIFY_THREAD_EX2_H_ */
