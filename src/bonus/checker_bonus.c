/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 10:03:46 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 10:04:57 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"
#include "checker_bonus.h"
#include "utils.h"

int	get_operation(const char *line, t_operation *op)
{
	if (!ft_strcmp(line, "sa"))
		*op = OP_SA;
	else if (!ft_strcmp(line, "sb"))
		*op = OP_SB;
	else if (!ft_strcmp(line, "ss"))
		*op = OP_SS;
	else if (!ft_strcmp(line, "pa"))
		*op = OP_PA;
	else if (!ft_strcmp(line, "pb"))
		*op = OP_PB;
	else if (!ft_strcmp(line, "ra"))
		*op = OP_RA;
	else if (!ft_strcmp(line, "rb"))
		*op = OP_RB;
	else if (!ft_strcmp(line, "rr"))
		*op = OP_RR;
	else if (!ft_strcmp(line, "rra"))
		*op = OP_RRA;
	else if (!ft_strcmp(line, "rrb"))
		*op = OP_RRB;
	else if (!ft_strcmp(line, "rrr"))
		*op = OP_RRR;
	else
		return (0);
	return (1);
}

// pridat kontrolu, ctx->ops_error, aby se zpracování zastavilo při chybě
static void	execute_ops(t_context *ctx)
{
	size_t	i;

	i = 0;
	while (i < ctx->ops_size)
	{
		exec(ctx, ctx->ops[i]);
		i++;
	}
}

static int	check_result(t_context *ctx)
{
	if (is_sorted(&ctx->a) && ctx->b.size == 0)
		put_str(1, "OK\n");
	else
		put_str(1, "KO\n");
	return (0);
}

int	main(int ac, char **av)
{
	t_args		args;
	t_context	ctx;

	if (ac < 2)
		return (0);
	if (!parse_args(ac, av, &args, 1))
		return (put_str(2, "Error\n"), 1);
	if (!init_context(&ctx, &args))
		return (free(args.array), put_str(2, "Error\n"), 1);
	free(args.array);
	if (!checker_read(&ctx))
		return (free_context(&ctx), put_str(2, "Error\n"), 1);
	ctx.record_ops = 0;
	execute_ops(&ctx);
	check_result(&ctx);
	free_context(&ctx);
	return (0);
}
