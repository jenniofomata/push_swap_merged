/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenofoma <jenofoma@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 20:00:00 by jenofoma          #+#    #+#             */
/*   Updated: 2026/11/19 21:00:00 by jenofoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	target_pos(const t_stack *a, int v)
{
	size_t	i;
	int		prev;

	i = 0;
	while (i < a->size)
	{
		prev = a->arr[(i + a->size - 1) % a->size];
		if (prev < v && v < a->arr[i])
			return ((int)i);
		i++;
	}
	return ((int)get_min_index(a));
}

static int	rot_steps(int idx, int size)
{
	if (idx <= size - idx)
		return (idx);
	return (idx - size);
}

static int	combo_cost(int ta, int tb)
{
	if ((ta >= 0 && tb >= 0) || (ta <= 0 && tb <= 0))
	{
		if (ft_abs(ta) > ft_abs(tb))
			return (ft_abs(ta));
		return (ft_abs(tb));
	}
	return (ft_abs(ta) + ft_abs(tb));
}

static int	best_index(t_context *ctx, int *ta, int *tb)
{
	int	j;
	int	best;
	int	cost;
	int	bestcost;

	best = 0;
	bestcost = 2147483647;
	j = 0;
	while (j < (int)ctx->b.size)
	{
		*ta = rot_steps(target_pos(&ctx->a, ctx->b.arr[j]), ctx->a.size);
		*tb = rot_steps(j, ctx->b.size);
		cost = combo_cost(*ta, *tb);
		if (cost < bestcost)
		{
			bestcost = cost;
			best = j;
		}
		j++;
	}
	*ta = rot_steps(target_pos(&ctx->a, ctx->b.arr[best]), ctx->a.size);
	*tb = rot_steps(best, ctx->b.size);
	return (best);
}

void	insert_all(t_context *ctx)
{
	int	ta;
	int	tb;

	while (ctx->b.size > 0 && !ctx->ops_error)
	{
		best_index(ctx, &ta, &tb);
		apply_both(ctx, &ta, &tb);
		apply_rest(ctx, ta, tb);
		exec(ctx, OP_PA);
	}
	rotate_to_top(ctx, get_min_index(&ctx->a));
}
