/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:45:27 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 15:36:01 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"
#include "utils.h"

static void	init_context_data(t_context *ctx, t_args *args)
{
	ctx->a = (t_stack){0};
	ctx->b = (t_stack){0};
	ctx->ops = NULL;
	ctx->ops_size = 0;
	ctx->ops_cap = 0;
	ctx->ops_error = 0;
	ctx->record_ops = 1;
	ctx->config.is_bench = args->bench;
	ctx->config.is_strategy_set = args->strategy_set;
	ctx->config.strategy = args->strategy;
	ft_memset(&ctx->opcount, 0, sizeof(ctx->opcount));
	ctx->disorder = 0.0;
	ctx->used_strategy = S_ADAPTIVE;
	ctx->method = NULL;
}

static int	init_context_stacks(t_context *ctx, t_args *args)
{
	size_t	i;
	size_t	total;

	total = (size_t)args->size;
	if (!init_stack(&ctx->a, total))
		return (0);
	if (!init_stack(&ctx->b, total))
		return (0);
	i = 0;
	while (i < total)
	{
		ctx->a.arr[i] = args->array[i];
		i++;
	}
	ctx->a.size = total;
	if (!normalize_stack(&ctx->a))
		return (0);
	return (1);
}

int	init_context(t_context *ctx, t_args *args)
{
	init_context_data(ctx, args);
	if (!init_context_stacks(ctx, args))
		return (free_context(ctx), 0);
	return (1);
}

void	free_context(t_context *ctx)
{
	free(ctx->ops);
	ctx->ops = NULL;
	ctx->ops_size = 0;
	ctx->ops_cap = 0;
	free_stack(&ctx->a);
	free_stack(&ctx->b);
}
