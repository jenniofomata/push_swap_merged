/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkohoute <mkohoute@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:46:58 by mkohoute          #+#    #+#             */
/*   Updated: 2026/11/17 16:31:28 by mkohoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"
#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (n--)
		((unsigned char *)dest)[n] = ((const unsigned char *)src)[n];
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	while (n--)
		((unsigned char *)s)[n] = (unsigned char)c;
	return (s);
}

void	*ft_grow(void *ptr, size_t used, size_t size)
{
	void	*fresh;

	fresh = malloc(size);
	if (!fresh)
		return (NULL);
	if (used)
		ft_memcpy(fresh, ptr, used);
	free(ptr);
	return (fresh);
}
