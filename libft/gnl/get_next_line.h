/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 15:40:02 by brian             #+#    #+#             */
/*   Updated: 2025/08/29 15:45:46 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

#define BUFFER_SIZE 1024

typedef struct		s_gnl
{
	struct s_gnl	*next;
	int				fd;
	int				asleft;
	int				nbr_read;
	int				eol;
	char			*buff;
}					t_gnl;

int					get_next_line(int fd, char **line);
int					has_eol(char *s);
char				*ft_strnjoin(char const *s1,
					char const *s2,
					int start,
					int size);
size_t				ft_gnl_strlen(const char *s);
void				*ft_gnl_calloc(size_t count, size_t size);
#endif
