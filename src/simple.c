/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 08:16:28 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 18:19:49 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "push_swap.h"

static void	sort_three(t_context *ctx)
{
	int	a;
	int	b;
	int	c;

	a = ctx->a.arr[0];
	b = ctx->a.arr[1];
	c = ctx->a.arr[2];
	if (a > b && b < c && a < c)
		exec(ctx, OP_SA);
	else if (a > b && b > c)
	{
		exec(ctx, OP_SA);
		exec(ctx, OP_RRA);
	}
	else if (a > b && b < c && a > c)
		exec(ctx, OP_RA);
	else if (a < b && b > c && a < c)
	{
		exec(ctx, OP_SA);
		exec(ctx, OP_RA);
	}
	else if (a < b && b > c && a > c)
		exec(ctx, OP_RRA);
}

void	sort_simple(t_context *ctx)
{
	size_t	min_i;

	if (ctx->a.size < 2)
		return ;
	if (ctx->a.size == 2)
	{
		if (ctx->a.arr[0] > ctx->a.arr[1])
			exec(ctx, OP_SA);
	}
	else
	{
		while (ctx->a.size > 3 && !ctx->ops_error)
		{
			min_i = get_min_index(&ctx->a);
			rotate_to_top(ctx, min_i);
			if (!ctx->ops_error)
				exec(ctx, OP_PB);
		}
		if (!ctx->ops_error)
			sort_three(ctx);
		while (ctx->b.size > 0 && !ctx->ops_error)
			exec(ctx, OP_PA);
	}
}
