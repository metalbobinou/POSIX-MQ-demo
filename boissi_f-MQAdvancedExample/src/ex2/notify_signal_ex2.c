#include "notify_signal_ex2.h"

/*
** The handler of the sigaction.
*/
void			my_signal_handler(int		signal,
					  siginfo_t	*siginfo,
					  void		*truc)
{
  printf("!! SIGNAL : OMG OMG OMG ! A signal was sent !\n");
  printf("!! Informations - Signal : %d\nSignal (siginfo) %d\nSigvalue : %d\n",
	 signal,
	 siginfo->si_signo,
	 siginfo->si_value.sival_int); /* union sigval accessed */
  truc = truc;
}

/*
** A function that ask the system to catch a signal.
*/
void			catch_signal(int	signo)
{
  struct sigaction	sa;

  sa.sa_flags = SA_SIGINFO;
  sa.sa_sigaction = my_signal_handler;
  sigemptyset(&sa.sa_mask);
  sigaction(signo, &sa, NULL);
}
