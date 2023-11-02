/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 10:26:15 by dliu          #+#    #+#                 */
/*   Updated: 2023/01/25 13:57:59 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_and_save(int fd, char *save, size_t *len);
size_t		find_nl(const char *s);
char		*cpycat(char *cpy, size_t cpystart, char *cat, size_t tlen);

char	*get_next_line(int fd)
{
	static char	*save[4069];
	char		*line;
	size_t		len;
	size_t		nlen;

	if (fd < 0 || fd > 4069 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	len = 0;
	line = NULL;
	while (save[fd] && save[fd][len])
		len++;
	save[fd] = read_and_save(fd, save[fd], &len);
	if (save[fd])
		line = cpycat(NULL, 0, save[fd], len);
	if (line)
	{
		nlen = 0;
		while (*(save[fd] + len + nlen))
			nlen++;
		save[fd] = cpycat(save[fd], len, NULL, nlen);
		return (line);
	}
	free(save[fd]);
	save[fd] = NULL;
	return (NULL);
}

static char	*read_and_save(int fd, char *save, size_t *len)
{
	char	buffer[BUFFER_SIZE + 1];
	size_t	nl;
	ssize_t	rcount;

	nl = find_nl(save);
	while (!nl)
	{
		rcount = read(fd, buffer, BUFFER_SIZE);
		if (rcount < 0)
		{
			free(save);
			return (NULL);
		}
		buffer[rcount] = '\0';
		if (rcount == 0)
			break ;
		*len += rcount;
		save = cpycat(save, 0, buffer, *len);
		if (!save)
			return (NULL);
		nl = find_nl(save);
	}
	if (nl)
		*len = nl;
	return (save);
}

size_t	find_nl(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\n')
			return (++i);
		i++;
	}
	return (0);
}

char	*cpycat(char *cpy, size_t cpystart, char *cat, size_t tlen)
{
	char	*newstr;
	size_t	i;

	newstr = NULL;
	if (tlen > 0 && (cpy || cat))
		newstr = malloc(tlen + 1);
	if (newstr)
	{
		i = 0;
		while (cpy && cpy[cpystart + i] && i < tlen)
		{
			newstr[i] = cpy[cpystart + i];
			i++;
		}
		while (cat && *cat && i < tlen)
		{
			newstr[i] = *cat++;
			i++;
		}
		newstr[i] = '\0';
	}
	free(cpy);
	return (newstr);
}
