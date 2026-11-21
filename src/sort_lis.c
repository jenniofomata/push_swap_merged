/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenofoma <jenofoma@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 20:00:00 by jenofoma          #+#    #+#             */
/*   Updated: 2026/11/19 21:00:00 by jenofoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

static void	lis_lengths(const t_stack *a, int *len)
{
	int	i;
	int	j;

	i = (int)a->size - 1;
	while (i >= 0)
	{
		len[i] = 1;
		j = i + 1;
		while (j < (int)a->size)
		{
			if (a->arr[j] > a->arr[i] && len[j] + 1 > len[i])
				len[i] = len[j] + 1;
			j++;
		}
		i--;
	}
}

static int	find_best(const int *len, int size)
{
	int	i;
	int	best;

	best = 0;
	i = 1;
	while (i < size)
	{
		if (len[i] > len[best])
			best = i;
		i++;
	}
	return (best);
}

static void	mark_keep(const t_stack *a, const int *len, int *keep)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)a->size)
		keep[i++] = 0;
	i = find_best(len, (int)a->size);
	keep[i] = 1;
	j = i + 1;
	while (j < (int)a->size)
	{
		if (len[j] == len[i] - 1 && a->arr[j] > a->arr[i])
		{
			keep[j] = 1;
			i = j;
		}
		j++;
	}
}

static void	strip_to_lis(t_context *ctx, const int *keep)
{
	int	i;
	int	size;

	i = 0;
	size = (int)ctx->a.size;
	while (i < size && !ctx->ops_error)
	{
		if (keep[i])
			exec(ctx, OP_RA);
		else
			exec(ctx, OP_PB);
		i++;
	}
}

void	sort_lis(t_context *ctx)
{
	int	*len;
	int	*keep;

	len = malloc(sizeof(int) * ctx->a.size);
	keep = malloc(sizeof(int) * ctx->a.size);
	if (!len || !keep)
	{
		free(len);
		free(keep);
		sort_medium(ctx);
		return ;
	}
	lis_lengths(&ctx->a, len);
	mark_keep(&ctx->a, len, keep);
	strip_to_lis(ctx, keep);
	free(len);
	free(keep);
	insert_all(ctx);
}
