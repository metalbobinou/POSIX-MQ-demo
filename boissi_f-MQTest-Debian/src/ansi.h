#ifndef ANSI_H_
# define ANSI_H_

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <string.h>
# include <errno.h>

# define MAXLINE	4096

int	snprintf(char		*buf,
		 size_t		size,
		 const char	*fmt, ...);

size_t	strnlen(const char	*s,
		size_t		maxlen);

char	*strdup(const char	*str);

char	*strndup(const char	*str,
		 size_t		len);

#endif /* !ANSI_H_ */
