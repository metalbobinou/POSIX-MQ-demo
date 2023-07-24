#include "ansi.h"

size_t	strnlen(const char	*s,
		size_t		maxlen)
{
  size_t	len;

  for (len = 0; len < maxlen; len++, s++)
  {
    if (!*s)
      break;
  }
  return (len);
}

char	*strdup(const char	*str)
{
  size_t	len;
  char		*copy;

  len = strlen(str) + 1;
  if ((copy = malloc(len * sizeof (char))) == NULL)
    return (NULL);
  memcpy(copy, str, len);
  return (copy);
}

char	*strndup(const char	*str,
		 size_t		n)
{
  size_t	len;
  char	*copy;

  len = strnlen(str, n);
  if ((copy = malloc(len + 1)) == NULL)
    return (NULL);
  memcpy(copy, str, len);
  copy[len] = '\0';
  return (copy);
}
