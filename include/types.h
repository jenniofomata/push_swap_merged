/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 09:19:26 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/17 09:19:26 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stddef.h>

/* ************************************************************************** */
/*                                  ENUMS                                     */
/* ************************************************************************** */

typedef enum e_strategy
{
	S_ADAPTIVE,
	S_SIMPLE,
	S_MEDIUM,
	S_COMPLEX
}	t_strategy;

typedef enum e_parse_status
{
	PARSE_OK,
	PARSE_EMPTY,
	PARSE_INVALID,
	PARSE_OVERFLOW,
	PARSE_DUPLICATE,
	PARSE_ALLOC,
	PARSE_BAD_OPTION,
	PARSE_MISSING_VALUE,
	PARSE_ERROR,
}	t_parse_status;

typedef enum e_operation
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_COUNT
}	t_operation;

/* ************************************************************************** */
/*                                STRUCTURES                                  */
/* ************************************************************************** */

typedef struct s_stack
{
	int		*arr;
	size_t	size;
	size_t	cap;
}	t_stack;

typedef struct s_config
{
	int			is_bench;
	int			is_strategy_set;
	t_strategy	strategy;
}	t_config;

typedef struct s_opcount
{
	size_t	sa;
	size_t	sb;
	size_t	ss;
	size_t	pa;
	size_t	pb;
	size_t	ra;
	size_t	rb;
	size_t	rr;
	size_t	rra;
	size_t	rrb;
	size_t	rrr;
}	t_opcount;

typedef struct s_args
{
	int			*array;
	int			size;
	int			pos;
	int			bench;
	int			strategy_set;
	t_strategy	strategy;
}	t_args;

typedef struct s_context
{
	t_stack		a;
	t_stack		b;
	t_config	config;
	t_opcount	opcount;
	t_operation	*ops;
	size_t		ops_size;
	size_t		ops_cap;
	int			ops_error;
	double		disorder;
	int			record_ops;
	t_strategy	used_strategy;
	const char	*method;
}	t_context;

#endif