/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 17:48:48 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 17:52:25 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "push_swap.h"
#include "utils.h"

int	count_capacity(int ac, char **av)
{
	const char	*s;
	int			count;
	int			is_num;
	int			i;

	count = 0;
	i = 0;
	while (++i < ac)
	{
		s = av[i];
		is_num = 1;
		while (*s)
		{
			if (is_space(*s))
				is_num = 1;
			else if (!is_digit(*s) && !is_sign(*s))
				is_num = 0;
			if (!is_space(*s) && (!s[1] || is_space(s[1])))
				if (is_num)
					count++;
			s++;
		}
	}
	return (count);
}

double	calculate_disorder(const t_stack *stack)
{
	size_t	i;
	size_t	j;
	size_t	disordered;
	size_t	total;

	if (stack->size < 2)
		return (0.0);
	disordered = 0;
	total = stack->size * (stack->size - 1) / 2;
	i = 0;
	while (i < stack->size)
	{
		j = i + 1;
		while (j < stack->size)
		{
			if (stack->arr[i] > stack->arr[j])
				disordered++;
			j++;
		}
		i++;
	}
	return ((double)disordered / (double)total);
}

t_parse_status	check_duplicates(const int *array, size_t size)
{
	const int	*current;
	const int	*next;

	current = array;
	while (current < array + size)
	{
		next = current + 1;
		while (next < array + size)
		{
			if (*current == *next)
				return (PARSE_DUPLICATE);
			next++;
		}
		current++;
	}
	return (PARSE_OK);
}
