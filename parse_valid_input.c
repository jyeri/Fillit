/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_valid_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsamoilo <nsamoilo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 11:32:45 by nsamoilo          #+#    #+#             */
/*   Updated: 2022/01/11 16:48:55 by nsamoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	find_equal(t_tetr *tetriminos, int index, t_tetr *current)
{
	current->prev = index + 1;
	while (index >= 0)
	{
		if (check_equal(find_tetropoint(*current),
				find_tetropoint(tetriminos[index]), *current,
				tetriminos[index]))
		{
			current->prev = index;
			return ;
		}
		index--;
	}
}

int	copy_tetr(char *buffer, int index, t_tetr *tetriminos, int i)
{
	int	row;
	int	letter;

	row = 0;
	tetriminos[i].grid = (char **)malloc(sizeof(char *) * 4);
	if (!tetriminos[i].grid)
		free_tetriminos(tetriminos, buffer, i - 1, 3);
	while (row < 4)
	{
		tetriminos[i].grid[row] = (char *)malloc(sizeof(char) * 5);
		if (!tetriminos[i].grid[row])
			free_tetriminos(tetriminos, buffer, i, row - 1);
		letter = 0;
		while (letter < 4)
		{
			tetriminos[i].grid[row][letter] = buffer[index];
			index++;
			letter++;
		}
		index++;
		row++;
	}
	tetriminos[i].symbol = 'A' + i;
	return (index);
}

t_tetr_array	parse_input(char *buffer)
{
	t_tetr			*tetriminos;
	t_tetr_array	array;
	int				i;
	int				index;
	int				amount;

	i = 0;
	index = 0;
	amount = (ft_strlen(buffer) + 1) / 21;
	tetriminos = (t_tetr *)malloc(sizeof(t_tetr) * amount + 1);
	if (!tetriminos)
	{
		free(buffer);
		exit(-1);
	}
	while (i < amount)
	{
		index = copy_tetr(buffer, index, tetriminos, i) + 1;
		find_equal(tetriminos, i - 1, &tetriminos[i]);
		i++;
	}
	array.array = tetriminos;
	array.size = amount;
	free(buffer);
	return (array);
}
