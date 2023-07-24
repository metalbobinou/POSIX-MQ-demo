#ifndef NOTIFY_SIGNAL_EX2_H_
# define NOTIFY_SIGNAL_EX2_H_

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>

/*
** The handler of the sigaction.
*/
void			my_signal_handler(int		signal,
					  siginfo_t	*siginfo,
					  void		*truc);

/*
** A function that ask the system to catch a signal.
*/
void			catch_signal(int	signo);

#endif /* !NOTIFY_SIGNAL_EX2_H_ */
