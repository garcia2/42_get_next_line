/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 00:06:08 by nico              #+#    #+#             */
/*   Updated: 2022/05/31 11:37:52 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	find_new_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static int	get_next(int fd, char **next)
{
	ssize_t	size_read;
	char	*buffer;
	char	*cur;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (0);
	size_read = read(fd, buffer, BUFFER_SIZE);
	if (size_read <= 0)
		return (free(buffer), 0);
	cur = *next;
	buffer[size_read] = '\0';
	*next = ft_strjoin(cur, buffer);
	if (cur != NULL)
		free(cur);
	if (find_new_line(*next) != -1 || size_read != BUFFER_SIZE)
		return (free(buffer), 0);
	free(buffer);
	return (1);
}

static char	*restore(char **rest)
{
	char	*next_line;

	if (*rest != NULL)
	{
		next_line = ft_strdup(*rest);
		free(*rest);
		*rest = NULL;
	}
	else
		next_line = ft_strdup("");
	return (next_line);
}

static char	*critical_free(char	*next_line)
{
	if (next_line != NULL)
		free(next_line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*rest;
	int			new_line_id;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	next_line = restore(&rest);
	if (next_line == NULL)
		return (NULL);
	while (get_next(fd, &next_line))
		;
	new_line_id = find_new_line(next_line);
	if (new_line_id != -1)
	{
		rest = ft_strdup(next_line + new_line_id + 1);
		if (rest == NULL)
			return (critical_free(next_line));
		next_line[new_line_id + 1] = '\0';
		next_line = restore(&next_line);
		if (next_line == NULL)
			return (critical_free(rest));
	}
	else if (next_line[0] == '\0')
		return (critical_free(next_line));
	return (next_line);
}
