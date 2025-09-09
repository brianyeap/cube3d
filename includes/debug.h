/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:47:32 by brian             #+#    #+#             */
/*   Updated: 2025/09/05 18:22:47 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

typedef struct s_map	t_map;

char	int_to_tile(int v);
int		check_map(t_map *m);
void	debug_print_map_pretty(t_map *m);

#endif