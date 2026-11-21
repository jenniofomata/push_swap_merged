/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 16:25:51 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 15:37:30 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_strategy	choose_strategy(const t_context *ctx)
{
	if (ctx->disorder < 0.2)
		return (S_SIMPLE);
	if (ctx->disorder < 0.5)
		return (S_MEDIUM);
	return (S_COMPLEX);
}

static const char	*method_name(const t_context *ctx)
{
	if (ctx->a.size <= SORT_SMALL_MAX)
		return ("small");
	if (ctx->used_strategy == S_SIMPLE)
		return ("lis");
	if (ctx->used_strategy == S_MEDIUM)
		return ("chunk");
	return ("radix");
}

void	run_sort(t_context *ctx)
{
	if (ctx->a.size < 2 || is_sorted(&ctx->a))
		return ;
	ctx->used_strategy = ctx->config.strategy;
	if (ctx->used_strategy == S_ADAPTIVE)
	{
		ctx->used_strategy = choose_strategy(ctx);
		ctx->method = method_name(ctx);
	}
	if (ctx->used_strategy == S_SIMPLE && ctx->config.strategy == S_ADAPTIVE
		&& ctx->a.size > SORT_SMALL_MAX)
		sort_lis(ctx);
	else if (ctx->used_strategy == S_SIMPLE)
		sort_simple(ctx);
	else if (ctx->used_strategy == S_MEDIUM)
		sort_medium(ctx);
	else if (ctx->used_strategy == S_COMPLEX)
		sort_complex(ctx);
}
