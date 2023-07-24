#ifndef ANSI_H_
# define ANSI_H_

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define MAXLINE	4096

size_t	strnlen(const char	*s,
		size_t		maxlen);

char	*strdup(const char	*str);

char	*strndup(const char	*str,
		 size_t		len);

ssize_t	getline(char	**linep,
		size_t	*linecapp,
		FILE	*stream);

#endif /* !ANSI_H_ */
