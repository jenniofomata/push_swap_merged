/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_rot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenofoma <jenofoma@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 20:00:00 by jenofoma          #+#    #+#             */
/*   Updated: 2026/11/19 21:00:00 by jenofoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "push_swap.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	apply_both(t_context *ctx, int *ta, int *tb)
{
	while (*ta > 0 && *tb > 0)
	{
		exec(ctx, OP_RR);
		(*ta)--;
		(*tb)--;
	}
	while (*ta < 0 && *tb < 0)
	{
		exec(ctx, OP_RRR);
		(*ta)++;
		(*tb)++;
	}
}

void	apply_rest(t_context *ctx, int ta, int tb)
{
	while (ta > 0)
	{
		exec(ctx, OP_RA);
		ta--;
	}
	while (ta < 0)
	{
		exec(ctx, OP_RRA);
		ta++;
	}
	while (tb > 0)
	{
		exec(ctx, OP_RB);
		tb--;
	}
	while (tb < 0)
	{
		exec(ctx, OP_RRB);
		tb++;
	}
}
