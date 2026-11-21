/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 07:21:27 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 18:20:41 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static size_t	isqrt(size_t n)
{
	size_t	root;

	root = 0;
	while (root + 1 <= n / (root + 1))
		root++;
	return (root);
}

static size_t	find_max_pos(const t_stack *stack)
{
	size_t	i;
	size_t	max_pos;

	i = 1;
	max_pos = 0;
	while (i < stack->size)
	{
		if (stack->arr[i] > stack->arr[max_pos])
			max_pos = i;
		i++;
	}
	return (max_pos);
}

static void	rotate_b_to_top(t_context *ctx, size_t pos)
{
	size_t	rotations;

	if (pos <= ctx->b.size / 2)
	{
		while (pos > 0 && !ctx->ops_error)
		{
			exec(ctx, OP_RB);
			pos--;
		}
	}
	else
	{
		rotations = ctx->b.size - pos;
		while (rotations > 0 && !ctx->ops_error)
		{
			exec(ctx, OP_RRB);
			rotations--;
		}
	}
}

static void	push_chunks(t_context *ctx, size_t chunk_size)
{
	size_t	pushed;
	int		rank;

	pushed = 0;
	while (ctx->a.size > 0 && !ctx->ops_error)
	{
		rank = ctx->a.arr[0];
		if ((size_t)rank < pushed + chunk_size)
		{
			exec(ctx, OP_PB);
			if (ctx->ops_error)
				break ;
			if ((size_t)rank < pushed)
				exec(ctx, OP_RB);
			pushed++;
		}
		else
			exec(ctx, OP_RA);
	}
}

void	sort_medium(t_context *ctx)
{
	size_t	chunk_size;
	size_t	max_pos;

	if (ctx->ops_error || ctx->a.size < 2 || is_sorted(&ctx->a))
		return ;
	if (ctx->a.size <= SORT_SMALL_MAX)
	{
		sort_simple(ctx);
		return ;
	}
	chunk_size = 3 * isqrt(ctx->a.size) / 2;
	if (chunk_size < 1)
		chunk_size = 1;
	push_chunks(ctx, chunk_size);
	while (ctx->b.size > 0 && !ctx->ops_error)
	{
		max_pos = find_max_pos(&ctx->b);
		rotate_b_to_top(ctx, max_pos);
		if (ctx->ops_error)
			break ;
		exec(ctx, OP_PA);
	}
}
