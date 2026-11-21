/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 19:10:46 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 09:31:43 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "push_swap.h"

void	print_count(const char *name, size_t count, const char *end)
{
	put_str(STDERR_FILENO, name);
	put_str(STDERR_FILENO, ": ");
	put_nbr(STDERR_FILENO, (long)count);
	put_str(STDERR_FILENO, end);
}

const char	*strategy_name(t_strategy strat)
{
	if (strat == S_SIMPLE)
		return ("Simple");
	if (strat == S_MEDIUM)
		return ("Medium");
	if (strat == S_COMPLEX)
		return ("Complex");
	return ("Adaptive");
}

const char	*complexity(t_strategy strat)
{
	if (strat == S_SIMPLE)
		return ("O(n^2)");
	if (strat == S_MEDIUM)
		return ("O(n*sqrt(n))");
	return ("O(n log n)");
}

void	print_disorder(double disorder)
{
	long	hundredths;

	hundredths = (long)(disorder * 10000.0 + 0.5);
	put_str(STDERR_FILENO, "[bench] disorder: ");
	put_nbr(STDERR_FILENO, hundredths / 100);
	put_str(STDERR_FILENO, ".");
	if (hundredths % 100 < 10)
		put_str(STDERR_FILENO, "0");
	put_nbr(STDERR_FILENO, hundredths % 100);
	put_str(STDERR_FILENO, "%\n");
}

void	print_opcount(const t_context *ctx)
{
	const t_opcount	*c;

	c = &ctx->opcount;
	print_count("[bench] sa", c->sa, " ");
	print_count("sb", c->sb, " ");
	print_count("ss", c->ss, " ");
	print_count("pa", c->pa, " ");
	print_count("pb", c->pb, "\n[bench] ");
	print_count("ra", c->ra, " ");
	print_count("rb", c->rb, " ");
	print_count("rr", c->rr, " ");
	print_count("rra", c->rra, " ");
	print_count("rrb", c->rrb, " ");
	print_count("rrr", c->rrr, "\n");
}
