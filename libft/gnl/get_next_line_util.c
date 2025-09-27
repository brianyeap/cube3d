/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:14:40 by brian             #+#    #+#             */
/*   Updated: 2025/09/28 00:16:16 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strnjoin(char const *s1, char const *s2, int start, int size)
{
	char		*join;
	size_t		i;
	size_t		j;
	size_t		s1len;
	size_t		s2len;

	s1len = ft_gnl_strlen(s1);
	s2len = ft_gnl_strlen(s2);
	i = 0;
	j = 0;
	if ((size_t)start > s2len)
		start = s2len;
	if ((size_t)size > s2len)
		size = s2len;
	join = malloc((s1len + size + 1) * sizeof(char));
	if (!join)
		return (NULL);
	while (j < s1len)
		join[i++] = s1[j++];
	j = start;
	while (j < s2len && size--)
		join[i++] = s2[j++];
	join[i] = '\0';
	return (join);
}

int	has_eol(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	*ft_gnl_calloc(size_t count, size_t size)
{
	void			*obj;
	unsigned char	*pobj;

	obj = malloc(count * size);
	if (obj != NULL)
	{
		pobj = obj;
		while (count--)
			*pobj++ = '\0';
	}
	return (obj);
}

size_t	ft_gnl_strlen(const char *s)
{
	size_t	length;

	length = 0;
	if (s)
		while (s[length])
			length++;
	return (length);
}

int	gnl_read_loop(t_gnl *b, t_gnl **blist, char **line)
{
	if (b->asleft && treat_left(b, line))
		return (1);
	if (!b->buff)
	{
		b->buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!b->buff)
			return (-1);
	}
	b->nbr_read = read(b->fd, b->buff, BUFFER_SIZE);
	while (b->nbr_read > 0)
	{
		b->buff[b->nbr_read] = 0;
		if (treat_left(b, line))
			return (1);
		b->nbr_read = read(b->fd, b->buff, BUFFER_SIZE);
	}
	if (b->nbr_read == 0)
	{
		meditate(blist, b, line);
		return (0);
	}
	return (-1);
}
