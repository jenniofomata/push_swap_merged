/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 09:16:57 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/17 09:16:57 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define SORT_SMALL_MAX 5

# include "types.h"

int				init_context(t_context *ctx, t_args *args);
void			free_context(t_context *ctx);

int				init_stack(t_stack *stack, size_t capacity);
void			free_stack(t_stack *stack);
int				normalize_stack(t_stack *stack);

size_t			get_min_index(const t_stack *a);
void			rotate_to_top(t_context *ctx, size_t index);

void			swap(t_stack *stack);
void			push(t_stack *dst, t_stack *src);
void			rotate(t_stack *stack);
void			reverse_rotate(t_stack *stack);

int				is_sorted(const t_stack *stack);

t_strategy		choose_strategy(const t_context *ctx);
void			run_sort(t_context *ctx);

void			sort_medium(t_context *ctx);
void			sort_complex(t_context *ctx);
void			sort_simple(t_context *ctx);
int				sort_small(t_context *ctx);

void			sort_lis(t_context *ctx);
void			insert_all(t_context *ctx);
int				ft_abs(int n);
void			apply_both(t_context *ctx, int *ta, int *tb);
void			apply_rest(t_context *ctx, int ta, int tb);

int				parse_args(int ac, char **av, t_args *args, int checker);
int				count_capacity(int ac, char **av);
t_parse_status	check_duplicates(const int *array, size_t size);

void			ft_write(int fd, const char *s, size_t len);
void			put_str(int fd, const char *s);
void			put_nbr(int fd, long n);
void			print_operations(const t_context *ctx);
void			print_bench(const t_context *ctx);

double			calculate_disorder(const t_stack *stack);

void			exec(t_context *ctx, t_operation op);
void			op_record(t_context *ctx, t_operation op);
void			op_count(t_opcount *count, t_operation op);
const char		*op_name(t_operation op);

void			print_count(const char *name, size_t count, const char *end);
const char		*strategy_name(t_strategy strat);
const char		*complexity(t_strategy strat);
void			print_disorder(double disorder);
void			print_opcount(const t_context *ctx);

#endif