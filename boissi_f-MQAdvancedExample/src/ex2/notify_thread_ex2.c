#include "notify_thread_ex2.h"

/*
** A function called when a thread is created
** (when the MQ is empty with notify THREAD)
*/
void	my_thread_handler(void)
{
  printf("!! THREAD : I'm a thread, and the queue is empty !\n");
}
