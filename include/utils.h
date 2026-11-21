/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 09:59:43 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/19 09:18:45 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

int				is_space(char c);
int				is_digit(char c);
int				is_sign(char c);
int				ft_strcmp(const char *s1, const char *s2);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_realloc(void *ptr, size_t size);

#endif