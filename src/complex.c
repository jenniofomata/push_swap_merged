/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:24:07 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 18:20:27 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_bits(size_t size)
{
	size_t	max;
	int		bits;

	max = size - 1;
	bits = 0;
	while (max > 0)
	{
		bits++;
		max >>= 1;
	}
	return (bits);
}

static void	radix_check(t_context *ctx, int bit)
{
	if (ctx->ops_error)
		return ;
	if ((ctx->a.arr[0] >> bit) & 1)
		exec(ctx, OP_RA);
	else
		exec(ctx, OP_PB);
}

static void	radix_sort(t_context *ctx, size_t total, int bits)
{
	size_t	j;
	int		i;

	i = 0;
	while (i < bits && !ctx->ops_error)
	{
		j = 0;
		while (j < total && !ctx->ops_error)
		{
			radix_check(ctx, i);
			j++;
		}
		while (ctx->b.size > 0 && !ctx->ops_error)
			exec(ctx, OP_PA);
		i++;
	}
}

void	sort_complex(t_context *ctx)
{
	size_t	total;
	int		bits;

	if (ctx->ops_error || ctx->a.size < 2 || is_sorted(&ctx->a))
		return ;
	if (ctx->a.size <= SORT_SMALL_MAX)
	{
		sort_simple(ctx);
		return ;
	}
	total = ctx->a.size + ctx->b.size;
	bits = get_max_bits(ctx->a.size);
	radix_sort(ctx, total, bits);
}
