/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:54:27 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/17 15:57:22 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "types.h"
#include "utils.h"

static size_t	get_rank(int *values, size_t size, int value)
{
	size_t	i;
	size_t	rank;

	i = 0;
	rank = 0;
	while (i < size)
	{
		if (values[i] < value)
			rank++;
		i++;
	}
	return (rank);
}

int	normalize_stack(t_stack *stack)
{
	int		*values;
	size_t	i;

	if (stack->size < 2)
		return (1);
	if (stack->size > (size_t)INT_MAX)
		return (0);
	values = malloc(sizeof(*values) * stack->size);
	if (!values)
		return (0);
	ft_memcpy(values, stack->arr, sizeof(*values) * stack->size);
	i = 0;
	while (i < stack->size)
	{
		stack->arr[i] = (int)get_rank(values, stack->size,
				values[i]);
		i++;
	}
	free(values);
	return (1);
}
