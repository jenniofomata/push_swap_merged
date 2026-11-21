/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 02:50:43 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 15:38:19 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "utils.h"
#include <stdlib.h>
#include <limits.h>

static t_parse_status	parse_int(const char **s, int *n)
{
	long	res;
	int		sign;

	sign = 1;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	if (!is_digit(**s))
		return (PARSE_INVALID);
	res = 0;
	while (is_digit(**s))
	{
		res = res * 10 + (**s - '0');
		if (res * sign > INT_MAX || res * sign < INT_MIN)
			return (PARSE_OVERFLOW);
		(*s)++;
	}
	if (**s && !is_space(**s))
		return (PARSE_INVALID);
	*n = (int)(res * sign);
	return (PARSE_OK);
}

static t_parse_status	parse_arg(const char *s, t_args *args)
{
	t_parse_status	status;
	int				n;

	while (is_space(*s))
		s++;
	if (!*s)
		return (PARSE_INVALID);
	while (*s)
	{
		while (is_space(*s))
			s++;
		if (!*s)
			break ;
		status = parse_int(&s, &n);
		if (status != PARSE_OK)
			return (status);
		args->array[args->pos] = n;
		args->pos++;
	}
	return (PARSE_OK);
}

static t_parse_status	parse_flag(const char *s, t_args *args)
{
	int	strat;

	if (!ft_strcmp(s, "--bench"))
	{
		if (args->bench)
			return (PARSE_INVALID);
		args->bench = 1;
		return (PARSE_OK);
	}
	if (args->strategy_set)
		return (PARSE_INVALID);
	strat = -1;
	if (!ft_strcmp(s, "--simple"))
		strat = S_SIMPLE;
	else if (!ft_strcmp(s, "--medium"))
		strat = S_MEDIUM;
	else if (!ft_strcmp(s, "--complex"))
		strat = S_COMPLEX;
	else if (!ft_strcmp(s, "--adaptive"))
		strat = S_ADAPTIVE;
	if (strat < 0)
		return (PARSE_INVALID);
	args->strategy = strat;
	args->strategy_set = 1;
	return (PARSE_OK);
}

static int	init_args(int ac, char **av, t_args *args)
{
	args->array = NULL;
	args->pos = 0;
	args->bench = 0;
	args->strategy_set = 0;
	args->strategy = S_ADAPTIVE;
	args->size = count_capacity(ac, av);
	if (args->size == 0)
		return (1);
	args->array = malloc(sizeof(*args->array) * args->size);
	if (!args->array)
		return (0);
	return (1);
}

int	parse_args(int ac, char **av, t_args *args, int checker)
{
	int				i;
	t_parse_status	status;

	if (!init_args(ac, av, args))
		return (0);
	status = PARSE_OK;
	i = 0;
	while (++i < ac)
	{
		if (!checker)
		{
			status = parse_flag(av[i], args);
			if (status == PARSE_OK)
				continue ;
		}
		status = parse_arg(av[i], args);
		if (status != PARSE_OK)
			break ;
	}
	if (status == PARSE_OK && args->pos == args->size)
		if (!args->size || !check_duplicates(args->array, args->size))
			return (1);
	free(args->array);
	args->array = NULL;
	return (0);
}
