/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 09:21:20 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 16:43:27 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack *stack)
{
	int	tmp;

	if (stack->size < 2)
		return ;
	tmp = stack->arr[0];
	stack->arr[0] = stack->arr[1];
	stack->arr[1] = tmp;
}

void	push(t_stack *dst, t_stack *src)
{
	size_t	i;

	if (src->size == 0 || dst->size >= dst->cap)
		return ;
	i = dst->size;
	while (i > 0)
	{
		dst->arr[i] = dst->arr[i - 1];
		i--;
	}
	dst->arr[0] = src->arr[0];
	dst->size++;
	i = 0;
	while (i + 1 < src->size)
	{
		src->arr[i] = src->arr[i + 1];
		i++;
	}
	src->size--;
}

void	rotate(t_stack *stack)
{
	int		tmp;
	size_t	i;

	if (stack->size < 2)
		return ;
	tmp = stack->arr[0];
	i = 0;
	while (i + 1 < stack->size)
	{
		stack->arr[i] = stack->arr[i + 1];
		i++;
	}
	stack->arr[stack->size - 1] = tmp;
}

void	reverse_rotate(t_stack *stack)
{
	int		tmp;
	size_t	i;

	if (stack->size < 2)
		return ;
	tmp = stack->arr[stack->size - 1];
	i = stack->size - 1;
	while (i > 0)
	{
		stack->arr[i] = stack->arr[i - 1];
		i--;
	}
	stack->arr[0] = tmp;
}

void	rotate_to_top(t_context *ctx, size_t index)
{
	size_t	rev;

	rev = ctx->a.size - index;
	if (index <= ctx->a.size / 2)
	{
		while (index-- > 0 && !ctx->ops_error)
			exec(ctx, OP_RA);
	}
	else
	{
		while (rev-- > 0 && !ctx->ops_error)
			exec(ctx, OP_RRA);
	}
}
