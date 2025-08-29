/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brian <brian@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:22:22 by brian             #+#    #+#             */
/*   Updated: 2025/08/29 16:13:06 by brian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"


#define MAPDBG 1
#if MAPDBG
#  define MAPPR(...) fprintf(stderr, __VA_ARGS__)
#else
#  define MAPPR(...)
#endif

static int report_fail(const char *side,
                       int cur, int nx, int ny, int verif,
                       int x, int y)
{
    MAPPR("[MAPCHK] fail at (%d,%d): cur=%d, neighbor %s (%d,%d)=%d",
          x, y, cur, side, nx, ny, verif);
    if (cur == 0 && verif == -1)
        MAPPR("  reason: floor next to VOID\n");
    else if (cur == -1 && verif != 1 && verif != -1)
        MAPPR("  reason: VOID touches non-wall (%d)\n", verif);
    else
        MAPPR("\n");
    return 0;
}

int check_surround(t_map *m, t_point *pos)
{
    int cur   = get_grid(m, pos->x, pos->y, 0);
    int nx, ny, verif;

    // UP
    nx = pos->x; ny = pos->y - 1;
    verif = get_grid(m, nx, ny, 0);
    if ((cur == 0 && verif == -1) || (cur == -1 && verif != 1 && verif != -1))
        return report_fail("UP", cur, nx, ny, verif, pos->x, pos->y);

    // DOWN
    nx = pos->x; ny = pos->y + 1;
    verif = get_grid(m, nx, ny, 0);
    if ((cur == 0 && verif == -1) || (cur == -1 && verif != 1 && verif != -1))
        return report_fail("DOWN", cur, nx, ny, verif, pos->x, pos->y);

    // LEFT
    nx = pos->x - 1; ny = pos->y;
    verif = get_grid(m, nx, ny, 0);
    if ((cur == 0 && verif == -1) || (cur == -1 && verif != 1 && verif != -1))
        return report_fail("LEFT", cur, nx, ny, verif, pos->x, pos->y);

    // RIGHT
    nx = pos->x + 1; ny = pos->y;
    verif = get_grid(m, nx, ny, 0);
    if ((cur == 0 && verif == -1) || (cur == -1 && verif != 1 && verif != -1))
        return report_fail("RIGHT", cur, nx, ny, verif, pos->x, pos->y);

    return 1;
}


int	check_map(t_map *m)
{
	t_point	pos;

	pos.x = 0;
	while (pos.x < m->width)
	{
		pos.y = 0;
		while (pos.y < m->height)
		{
			if (check_surround(m, &pos) == 0)
			{
				printf(RED"Map Invalid at [%d,%d]\n"RST, pos.x, pos.y);
				return (0);
			}
			pos.y++;
		}
		pos.x++;
	}
	printf(GRN"Map Validated\n"RST);
	return (1);
}
