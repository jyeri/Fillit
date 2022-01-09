/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:20:15 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/01/09 18:44:06 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	find_start_coordinate(t_matrix *m, t_tetr_array *tetros,
	int index, t_point *s)
{
	int		i;
	int		j;

	i = 0;
	while (i < m->size)
	{
		j = 0;
		while (j < m->size)
		{
			if (m->grid[i][j] ==
				tetros->array[tetros->array[index].prev].symbol)
			{
				s->row = i;
				s->column = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

t_point	get_next_coordinate(t_matrix m, int row, int column)
{
	t_point	point;

	point.row = -1;
	point.column = -1;
	while (row < m.size)
	{
		while (column < m.size)
		{
			if (m.grid[row][column] == '.')
			{
				point.row = row;
				point.column = column;
				return (point);
			}
			column++;
		}
		row++;
		column = 0;
	}
	return (point);
}

void	put_tetrimino(t_tetr_array *tetros,
	t_matrix *matrix, int size, int index)
{
	int		result;
	t_point	next;
	t_point	tetropoint;

	if (index == tetros->size)
		end_game(tetros, matrix);
	next.column = 0;
	next.row = 0;
	if (tetros->array[index].prev != index)
		find_start_coordinate(matrix, tetros, index, &next);
	tetropoint = find_tetropoint(tetros->array[index]);
	while (next.column != -1)
	{
		result = place_tetro(next, matrix, tetros->array[index], tetropoint);
		if (result == 1)
		{
			put_tetrimino(tetros, matrix, size, index + 1);
			remove_tetro(next, matrix, tetros->array[index]);
		}
		next = get_next_coordinate(*matrix, next.row, next.column + 1);
	}
}

int	create_matrix(t_matrix *matrix, int size, int i, int j)
{
	matrix->grid = (char **)malloc(sizeof(char *) * size);
	if (!matrix->grid)
	{
		free(matrix);
		return (-1);
	}
	while (i < size)
	{
		j = 0;
		matrix->grid[i] = (char *)malloc(sizeof(char) * size);
		if (!matrix->grid[i])
		{
			free_matrix(matrix, i);
			return (-1);
		}
		while (j < size)
		{
			matrix->grid[i][j] = '.';
			j++;
		}
		i++;
	}
	return (1);
}

int	find_best(t_tetr_array *tetriminos, int size)
{
	t_matrix	*new;

	new = (t_matrix *)malloc(sizeof(t_matrix));
	if (!new || create_matrix(new, size, 0, 0) == -1)
	{
		free_tetriminos(tetriminos->array, NULL, tetriminos->size - 1, 3);
		exit(-1);
	}
	new->size = size;
	put_tetrimino(tetriminos, new, size, 0);
	free_matrix(new, new->size);
	return (0);
}
