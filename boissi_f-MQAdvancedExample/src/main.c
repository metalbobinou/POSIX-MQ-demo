#include "main.h"

int	usage(char	*prog)
{
  printf("Usage : %s [ex1 | ex2]\n", prog);
  printf("ex1 is the simplest example (writing in parent.log and child.log\n");
  printf("ex2 is an example with timedsend/recv notify (signals & threads)\n");
  return (0);
}

int	main(int	argc,
	     char	**argv)
{
  if (argc > 1)
  {
    if (strcmp(argv[1], "ex1") == 0)
      return (simple_example());
    if (strcmp(argv[1], "ex2") == 0)
      return (complex_example());
    if (strcmp(argv[1], "--help") == 0)
      return (usage(argv[0]));
  }
  return (usage(argv[0]));
}
