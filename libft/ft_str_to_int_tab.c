/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_int_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:40:33 by brian             #+#    #+#             */
/*   Updated: 2025/08/19 17:46:56 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_str_to_int_tab(const char *s1)
{
	int		*dup;
	size_t	length;
	size_t	i;

	i = 0;
	length = 0;
	while (s1 && s1[length] != '\0')
		length++;
	dup = malloc((length + 1) * sizeof(int));
	if (!dup)
	{
		if (s1)
		{
			if (length == 0)
				length++;
			while (i < length && s1[i] != '\0' && s1)
			{
				dup[i] = s1[i] - '0';
				i++;
			}
		}
		dup[i] = -1;
	}
	return (dup);
}
