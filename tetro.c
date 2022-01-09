/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:37:13 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/01/09 18:11:04 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int	place_tetro(t_point start, t_matrix *matrix, t_tetr tetro, t_point point)
{
	int		i;
	int		j;
	t_point	pos;

	if (check_tetro(start, matrix, tetro, point))
	{
		i = point.column;
		j = point.row;
		while (j++ < 4)
		{
			while (i < 4)
			{
				if (tetro.grid[j - 1][i] == '#')
				{
					pos.row = start.row + j - 1 - point.row;
					pos.column = start.column + i - point.column;
					matrix->grid[pos.row][pos.column] = tetro.symbol;
				}
				i++;
			}
			i = 0;
		}
		return (1);
	}
	return (0);
}

int	check_tetro(t_point start, t_matrix *matrix, t_tetr tetro, t_point point)
{
	int		i;
	int		j;
	t_point	pos;

	i = point.column;
	j = point.row;
	while (j < 4)
	{
		while (i < 4)
		{
			if (tetro.grid[j][i] == '#')
			{
				pos.row = start.row + j - point.row;
				pos.column = start.column + i - point.column;
				if (pos.row < 0 || pos.row >= matrix->size
					|| pos.column < 0 || pos.column >= matrix->size
					|| matrix->grid[pos.row][pos.column] != '.')
					return (0);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

t_point	find_tetropoint(t_tetr tetro)
{
	int		i;
	int		j;
	t_point	tetropoint;

	tetropoint.row = 0;
	tetropoint.column = 0;
	j = 0;
	while (j < 4)
	{
		i = 0;
		while (i < 4)
		{
			if (tetro.grid[j][i] == '#')
			{
				tetropoint.row = j;
				tetropoint.column = i;
				return (tetropoint);
			}
			i++;
		}
		j++;
	}
	return (tetropoint);
}

int	remove_tetro(t_point start, t_matrix *matrix, t_tetr tetro)
{
	int		i;
	int		j;
	t_point	tetropoint;
	t_point	pos;

	tetropoint = find_tetropoint(tetro);
	i = tetropoint.column;
	j = tetropoint.row;
	while (j < 4)
	{
		while (i < 4)
		{
			if (tetro.grid[j][i] == '#')
			{
				pos.row = start.row + j - tetropoint.row;
				pos.column = start.column + i - tetropoint.column;
				matrix->grid[pos.row][pos.column] = '.';
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	check_equal(t_point first_p, t_point second_p,
	t_tetr first_t, t_tetr second_t)
{
	int		i;
	int		j;

	i = first_p.column;
	j = first_p.row;
	while (j < 4)
	{
		while (i < 4)
		{
			if (first_t.grid[j][i] == '#' && (second_p.column + i -
				first_p.column >= 4 || second_p.row + j - first_p.row >= 4 ||
				second_t.grid[second_p.row + j -
				first_p.row][second_p.column + i - first_p.column] != '#'))
			{
				return (0);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}
