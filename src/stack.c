/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 09:20:57 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 16:41:26 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"
#include "types.h"

int	init_stack(t_stack *stack, size_t capacity)
{
	stack->arr = NULL;
	stack->size = 0;
	stack->cap = 0;
	if (capacity == 0)
		return (1);
	stack->arr = malloc(capacity * sizeof(*stack->arr));
	if (!stack->arr)
		return (0);
	stack->cap = capacity;
	return (1);
}

void	free_stack(t_stack *stack)
{
	free(stack->arr);
	stack->arr = NULL;
	stack->size = 0;
	stack->cap = 0;
}

size_t	get_min_index(const t_stack *a)
{
	size_t	i;
	size_t	pos_min;

	i = 1;
	pos_min = 0;
	while (i < a->size)
	{
		if (a->arr[i] < a->arr[pos_min])
			pos_min = i;
		i++;
	}
	return (pos_min);
}

int	is_sorted(const t_stack *stack)
{
	size_t	i;

	i = 0;
	while (i + 1 < stack->size)
	{
		if (stack->arr[i] > stack->arr[i + 1])
			return (0);
		i++;
	}
	return (1);
}
