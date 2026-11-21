/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 09:28:33 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 09:33:12 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"

const char	*op_name(t_operation op)
{
	static const char	*names[OP_COUNT] = {
		"sa", "sb", "ss", "pa", "pb", "ra",
		"rb", "rr", "rra", "rrb", "rrr"
	};

	if (op < 0 || op >= OP_COUNT)
		return (NULL);
	return (names[op]);
}

static int	op_realloc(t_context *ctx)
{
	t_operation	*tmp;
	size_t		new_cap;

	if (ctx->ops_cap == 0)
		new_cap = 64;
	else
	{
		if (ctx->ops_cap > (size_t)(-1) / 2)
			return (0);
		new_cap = ctx->ops_cap * 2;
	}
	if (new_cap > (size_t)-1 / sizeof(*ctx->ops))
		return (0);
	tmp = ft_grow(ctx->ops, sizeof(*ctx->ops) * ctx->ops_size,
			sizeof(*ctx->ops) * new_cap);	
		if (!tmp)
		return (0);
	ctx->ops = tmp;
	ctx->ops_cap = new_cap;
	return (1);
}

void	op_count(t_opcount *count, t_operation op)
{
	if (op == OP_SA)
		count->sa++;
	else if (op == OP_SB)
		count->sb++;
	else if (op == OP_SS)
		count->ss++;
	else if (op == OP_PA)
		count->pa++;
	else if (op == OP_PB)
		count->pb++;
	else if (op == OP_RA)
		count->ra++;
	else if (op == OP_RB)
		count->rb++;
	else if (op == OP_RR)
		count->rr++;
	else if (op == OP_RRA)
		count->rra++;
	else if (op == OP_RRB)
		count->rrb++;
	else if (op == OP_RRR)
		count->rrr++;
}

void	op_record(t_context *ctx, t_operation op)
{
	if (!ctx->record_ops || ctx->ops_error)
		return ;
	if (ctx->ops_size == ctx->ops_cap)
	{
		if (!op_realloc(ctx))
		{
			ctx->ops_error = 1;
			return ;
		}
	}
	ctx->ops[ctx->ops_size] = op;
	ctx->ops_size++;
	op_count(&ctx->opcount, op);
}

void	exec(t_context *ctx, t_operation op)
{
	op_record(ctx, op);
	if (ctx->ops_error)
		return ;
	if (op == OP_SA || op == OP_SS)
		swap(&ctx->a);
	if (op == OP_SB || op == OP_SS)
		swap(&ctx->b);
	if (op == OP_PA)
		push(&ctx->a, &ctx->b);
	if (op == OP_PB)
		push(&ctx->b, &ctx->a);
	if (op == OP_RA || op == OP_RR)
		rotate(&ctx->a);
	if (op == OP_RB || op == OP_RR)
		rotate(&ctx->b);
	if (op == OP_RRA || op == OP_RRR)
		reverse_rotate(&ctx->a);
	if (op == OP_RRB || op == OP_RRR)
		reverse_rotate(&ctx->b);
}
