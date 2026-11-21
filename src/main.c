/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:45:05 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 15:27:03 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "push_swap.h"

static int	run(t_args *args)
{
	t_context	ctx;

	if (!init_context(&ctx, args))
	{
		free(args->array);
		put_str(STDERR_FILENO, "Error\n");
		return (1);
	}
	free(args->array);
	ctx.disorder = calculate_disorder(&ctx.a);
	run_sort(&ctx);
	if (ctx.ops_error)
	{
		put_str(STDERR_FILENO, "Error\n");
		free_context(&ctx);
		return (1);
	}
	print_operations(&ctx);
	if (ctx.config.is_bench)
		print_bench(&ctx);
	free_context(&ctx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc == 1)
		return (0);
	if (!parse_args(argc, argv, &args, 0))
	{
		put_str(STDERR_FILENO, "Error\n");
		return (1);
	}
	if (args.size == 0)
	{
		free(args.array);
		return (0);
	}
	return (run(&args));
}
