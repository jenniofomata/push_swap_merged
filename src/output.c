/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 17:55:48 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 17:44:29 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "push_swap.h"

void	ft_write(int fd, const char *s, size_t len)
{
	ssize_t	w;

	while (len > 0)
	{
		w = write(fd, s, len);
		if (w <= 0)
			return ;
		s += w;
		len -= (size_t)w;
	}
}

void	put_str(int fd, const char *s)
{
	const char	*end;

	end = s;
	while (*end)
		end++;
	ft_write(fd, s, end - s);
}

void	put_nbr(int fd, long n)
{
	char	c;

	if (n < 0)
	{
		put_str(fd, "-");
		n = -n;
	}
	if (n >= 10)
		put_nbr(fd, n / 10);
	c = '0' + n % 10;
	ft_write(fd, &c, 1);
}

void	print_operations(const t_context *ctx)
{
	const t_operation	*op;
	const char			*name;
	size_t				left;

	op = ctx->ops;
	left = ctx->ops_size;
	while (left > 0)
	{
		name = op_name(*op);
		if (name)
		{
			put_str(STDOUT_FILENO, name);
			put_str(STDOUT_FILENO, "\n");
		}
		op++;
		left--;
	}
}

void	print_bench(const t_context *ctx)
{
	print_disorder(ctx->disorder);
	put_str(STDERR_FILENO, "[bench] strategy: ");
	put_str(STDERR_FILENO, strategy_name(ctx->config.strategy));
	if (ctx->method)
	{
		put_str(STDERR_FILENO, " (");
		put_str(STDERR_FILENO, ctx->method);
		put_str(STDERR_FILENO, ")");
	}
	put_str(STDERR_FILENO, " / ");
	put_str(STDERR_FILENO, complexity(ctx->used_strategy));
	print_count("\n[bench] total_ops", ctx->ops_size, "\n");
	print_opcount(ctx);
}
