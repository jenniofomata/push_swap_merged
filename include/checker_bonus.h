/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 10:01:50 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 10:01:51 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include "types.h"

int	checker_read(t_context *ctx);
int	get_operation(const char *line, t_operation *op);

#endif